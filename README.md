*This project has been created as part of the 42 curriculum by sm*This project has been created as part of the 42 curriculum by smenard.*

# Codexion

## Description

Codexion is a concurrency simulation inspired by the classic Dining Philosophers
problem. Multiple coders sit around a shared Quantum Compiler, each needing two
USB dongles simultaneously to compile their code. The challenge is to orchestrate
resource sharing using POSIX threads, mutexes, and condition variables
— preventing deadlocks, starvation, and burnout.

Each coder cycles through three phases: **compiling** (requires 2 dongles),
**debugging**, and **refactoring**. A coder burns out if they don't start
compiling within `time_to_burnout` milliseconds since their last compile.
The simulation ends either when all coders have reached the required number
of compiles, or when one burns out.

Two scheduling policies are supported for dongle arbitration:
- **FIFO** — dongles are granted in request arrival order
- **EDF** (Earliest Deadline First) — the coder closest to burning out is served first

## Instructions

### Compilation

```bash
make
```

This produces the `codexion` executable at the root of the repository. Compiled with `-Wall -Wextra -Werror -pthread`.

### Usage

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug \
           time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

All arguments are mandatory. Times are in milliseconds. `scheduler` must be exactly `fifo` or `edf`.

### Example

```bash
# 4 coders, 800ms burnout, 200ms compile, 200ms debug, 400ms refactor
# each must compile 5 times, 10ms dongle cooldown, FIFO scheduling
./codexion 4 800 200 200 400 5 10 fifo
```

### Makefile rules

| Rule | Effect |
|------|--------|
| `make` / `make all` | Build the project |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and binary |
| `make re` | Full rebuild |
| `make run` | Run the program with default arguments |
| `make debug` | Compile with debug symbols and run the project in gdb |
| `make vg` | Run the program with valgrind |
| `make hg` | Run the program with valgrind in helgrind mode |
| `make run TIME_TO_BURNOUT=42` | Override the time to burnout argument and run the program |

**Overridable makefile variables**

| Variable | Effect |
|----------|--------|
| `NUMBER_OF_CODERS` | The number of coders to simulate |
| `TIME_TO_BURNOUT` | Time in ms since the start of the last compile task until a coder burns out |
| `TIME_TO_COMPILE` | Time in ms for the compile task |
| `TIME_TO_DEBUG` | Time in ms for the debug task |
| `TIME_TO_REFACTOR` | Time in ms for the refactor task |
| `NUMBER_OF_COMPILES_REQUIRED` | Number of iterations until a coder is done |
| `DONGLE_COOLDOWN` | Time until a dongle can be used again after being released |
| `SCHEDULER` (`fifo` / `edf`) | The scheduler used by the heap queue |
| `ARGUMENTS` | The entire arguments string passed to the executable |
| `LOG_LEVEL` | The log level of the program — use with `make re` as this value is compiled as a macro |

## Blocking cases handled

### Thread startup desync

When spawning threads in a loop, each thread starts with a slight delay relative
to the others. Over many iterations these small offsets compound, causing coders
to drift noticeably out of sync.

The fix relies on a startup barrier: the monitor holds a mutex locked while
creating all threads. Each coder thread tries to acquire that same mutex
immediately at startup, so it blocks until every thread exists. The monitor then
releases the mutex, letting all coders proceed at roughly the same time. The
residual desync is negligible, as mutex lock and unlock have near-zero overhead.

### Deadlocks with an odd number of coders

With an odd coder count, threads tend to grab dongles at the same pace, making
it likely that every coder picks up one dongle and then waits forever for the
second — a textbook circular wait deadlock.

Two complementary fixes address this. First, every coder always picks up their
left dongle before their right. On its own this is not enough to break
circularity, but combined with the second fix it guarantees that whoever holds a
left dongle will eventually get the matching right one. Second, coders with an
odd ID wait for half the compile duration before starting. This stagger creates a
natural alternation between even and odd coders, giving each pair enough time to
acquire both dongles before the other side can compete for them.

### Log serialization

`printf` is not thread-safe: concurrent calls from multiple coder threads can
interleave and produce garbled output. All logging therefore goes through a
dedicated wrapper that holds a log mutex for the duration of the write, ensuring
every message is printed atomically and in full.

## Thread synchronization mechanisms

### Dongle access — `pthread_mutex_t`

Each dongle has its own mutex that protects its state (in use or in cooldown).
When a coder needs a dongle that is not yet available, it inserts itself into the
dongle's heap queue and then spins in a tight loop, sleeping 10 µs between
iterations. On each wake-up it checks three conditions under the mutex: it must
be at the front of the queue, the dongle must not be in use, and the cooldown
must have expired. Only when all three are satisfied does it take the dongle and
remove itself from the queue.

### Scheduler — heap-based priority queue

Each dongle maintains a min-heap of pending requests. Under **FIFO** the key is
the request's arrival timestamp; under **EDF** it is the coder's burnout deadline
(`last_compile_start + time_to_burnout`). The heap is always accessed under the
dongle's own mutex, so insertion, removal, and peek are free of race conditions.
When two entries share the same key, coder ID is used as a tie-breaker to keep
the policy fully deterministic.

### Dongle cooldown

When a coder releases a dongle it records the current timestamp on the dongle.
Waiting coders check whether the cooldown has expired by comparing that timestamp
plus `dongle_cooldown` against the current time on every iteration of their
polling loop. No extra state is needed: if `now >= release_time + dongle_cooldown`
the dongle is considered available, otherwise the coder goes back to sleep for
another 10 µs.

### Monitor thread — `run` flag + `done` flag

A dedicated monitor thread periodically checks each coder's last compile
timestamp against `time_to_burnout`. On detecting a burnout it clears a shared
`run` flag under a mutex; coder threads check this flag at every phase transition
and exit cleanly, without risk of being left blocked on a condition wait.

The termination path works the other way around: each coder sets a per-coder
`done` flag when it reaches `number_of_compiles_required`. The monitor checks
all `done` flags before running burnout detection; once every coder is marked
done, it joins all threads before freeing heap memory and exiting, preventing
data races during cleanup.

### Log mutex

A single log mutex serializes all writes to stdout. Every thread — coder or
monitor — locks it before printing and releases it immediately after, preventing
output from interleaving across threads.

## Resources

### Concurrency & POSIX threads
- [POSIX Threads Programming — LLNL](https://hpc-tutorials.llnl.gov/posix/)
- [The Little Book of Semaphores — Allen B. Downey](https://greenteapress.com/wp/semaphores/)
- [pthread man pages — man7.org](https://man7.org/linux/man-pages/man7/pthreads.7.html)

### Scheduling
- [Earliest Deadline First scheduling — Wikipedia](https://en.wikipedia.org/wiki/Earliest_deadline_first_scheduling)
- [Priority queue / binary heap — Wikipedia](https://en.wikipedia.org/wiki/Binary_heap)

### AI usage

AI played a minor part in the development of this project. It was used during a
previous project to write a Makefile that was reused and adapted for this
codebase. It was also used to improve this README and, in a few exceptional
cases, to help track down bugs in the heap queue implementation.
