# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build & Run

```bash
make                    # build ./codexion
make run                # build and run with default args
make re                 # full rebuild
make clean / fclean     # remove objects / objects + binary
make debug              # compile with -g, launch in gdb
make vg                 # run under valgrind (leak check)
make hg                 # run under valgrind helgrind (race check)
```

**Override args at the command line:**
```bash
make run NUMBER_OF_CODERS=5 TIME_TO_BURNOUT=800 SCHEDULER=edf
make re LOG_LEVEL=0     # LOG_LEVEL is a compile-time macro — requires re
```

**Default arguments** (set in Makefile, all times in milliseconds):
| Variable | Default |
|---|---|
| `NUMBER_OF_CODERS` | 42 |
| `TIME_TO_BURNOUT` | 250 |
| `TIME_TO_COMPILE` | 60 |
| `TIME_TO_DEBUG` | 60 |
| `TIME_TO_REFACTOR` | 60 |
| `NUMBER_OF_COMPILES_REQUIRED` | 21 |
| `DONGLE_COOLDOWN` | 60 |
| `SCHEDULER` | fifo |

`LOG_LEVEL`: 0=DEBUG, 1=INFO (default), 2=WARN, 3=ERROR. Change requires `make re`.

**Code formatter:** `make format` (uses `python3 -m c_formatter_42`). This is a 42-norm formatter.

## Architecture

Codexion is a Dining Philosophers variant. Coders (philosophers) need two USB dongles (forks) simultaneously to compile. The simulation ends when all coders complete `number_of_compiles_required` cycles, or one burns out.

### Core types (`src/headers/defines.h`)

- `t_ctx` — top-level container: holds `t_dongle *dongles`, `t_coder *coders`, `t_scheduler_mode scheduler`, and `t_shared_ctx shared`.
- `t_shared_ctx` — parameters shared across all threads: timing values, `bool run` (simulation active flag), `pthread_mutex_t mutex` (guards `run`), `logging_mutex` (serializes stdout), `start` (startup barrier mutex).
- `t_coder` — per-coder state: `last_compile_timestamp`, `done` flag, pointers to left/right dongles, back-pointer to shared ctx, own `mutex`.
- `t_dongle` — per-dongle state: `in_use`, `last_use_timestamp`, `cooldown`, `t_heap_queue *hq` (pending requests), own `mutex`.
- `t_heap_queue` — min-heap used by each dongle for request arbitration; `get_key` function pointer selects FIFO or EDF policy.

### Thread model

`monitor_simulation()` (`src/monitor/monitor.c`) is the entry point after `init()`:
1. Locks `shared.start` mutex before spawning threads (startup barrier).
2. Creates one `pthread_t` per coder, each running `coder_routine()`.
3. Unlocks `shared.start` — all coder threads unblock simultaneously.
4. Polls `should_stop()` every 10 µs: detects burnout or all-done.
5. Sets `shared.run = false`, then joins all threads before returning.

`coder_routine()` (`src/coders/routine.c`):
- Blocks on `shared.start` mutex at startup (barrier), then records `last_compile_timestamp`.
- Odd-ID coders sleep for `time_to_compile` µs before entering the loop (deadlock stagger).
- Loops: `compile()` → `debug()` → `refactor()` until `shared.run` is false or iteration count reached.

### Dongle acquisition (`src/dongles/utils.c`, `src/coders/tasks.c`)

Coders always pick up their **left dongle first**, then right (prevents circular wait). Each dongle maintains a `t_heap_queue` of pending requestors:
1. `request_dongle()` — locks dongle mutex, inserts coder into heap queue, unlocks.
2. Coder spins (sleeping 10 µs between checks) until `can_take_dongle()` is true: coder is at front of heap, dongle not in use, cooldown expired.
3. `release_dongle()` — sets `in_use = false`, records `last_use_timestamp`.

### Scheduling policies (`src/schedulers/schedulers.c`)

The `get_key` function pointer on the heap queue controls ordering:
- **FIFO** (`get_key_fifo`): key = current timestamp at request time → arrival order.
- **EDF** (`get_key_edf`): key = `last_compile_timestamp + time_to_burnout` → soonest deadline first.

Tie-breaking within the heap uses coder ID (`src/heap_queue/`).

### Mutex lock ordering (avoid deadlocks in new code)

When multiple mutexes must be held simultaneously, always acquire in this order:
1. `coder->mutex`
2. `shared->mutex`
3. `shared->logging_mutex`

Never acquire a dongle mutex while holding a coder or shared mutex.

## Subject constraints

### Forbidden / not allowed
- **Global variables are forbidden**
- **libft is not authorized**
- No standard library priority queue — must implement custom heap

### Required
- Compile flags: `-Wall -Wextra -Werror -pthread`
- Makefile rules: `$(NAME)`, `all`, `clean`, `fclean`, `re`
- All heap-allocated memory must be freed (no leaks)

### Authorized external functions
```
pthread_create  pthread_join
pthread_mutex_init  pthread_mutex_lock  pthread_mutex_unlock  pthread_mutex_destroy
pthread_cond_init  pthread_cond_wait  pthread_cond_timedwait
pthread_cond_broadcast  pthread_cond_destroy
gettimeofday  usleep  write
malloc  free  printf  fprintf  strcmp  strlen  atoi  memset
```

### Argument validation
All 8 arguments are mandatory. Reject: negative numbers, non-integers, scheduler ≠ `fifo`/`edf`.

### Dongle topology
- Coders sit in a circle: coder 1 is adjacent to coder `number_of_coders`.
- **One dongle between each adjacent pair** → `number_of_coders` dongles total.
- Special case: if `number_of_coders == 1`, there is only one dongle.
- Coder N's left dongle = dongle N; right dongle = dongle N+1 (wraps around).

## Log format

Every state change must be printed as a single atomic line (protected by `logging_mutex`):

```
timestamp_in_ms X has taken a dongle
timestamp_in_ms X is compiling
timestamp_in_ms X is debugging
timestamp_in_ms X is refactoring
timestamp_in_ms X burned out
```

- `timestamp_in_ms`: milliseconds elapsed since simulation start (use `gettimeofday()`).
- `X`: coder number (1-based).
- A coder prints "has taken a dongle" **twice** before "is compiling" (once per dongle acquired).
- **Burnout precision**: the "burned out" log must appear within **10 ms** of the actual burnout time.
- Messages must never interleave (one mutex-protected write per message).

## README requirements

A `README.md` must exist at the repository root and include:

1. **First line** (italicized): `*This project has been created as part of the 42 curriculum by <login>.*`
2. **Description** — project goal and brief overview.
3. **Instructions** — compilation, installation, execution.
4. **Resources** — references (docs, articles, tutorials) and description of how AI was used (which tasks, which parts).
5. **Blocking cases handled** — describe solutions for: deadlock prevention (Coffman's conditions), starvation prevention, cooldown handling, precise burnout detection, log serialization.
6. **Thread synchronization mechanisms** — explain use of `pthread_mutex_t`, `pthread_cond_t`, custom event implementation; how race conditions are prevented; how thread-safe communication works between coders and the monitor.

README must be written in English.

## Project layout

```
src/
  main.c               # parse → init → monitor → free
  headers/             # defines.h (all types), includes.h, lib.h (umbrella)
  init/                # init.c, coders.c, dongles.c, ctx.c
  coders/              # routine.c (thread entry), tasks.c (compile/debug/refactor), utils.c
  monitor/             # monitor.c (thread lifecycle + burnout detection)
  dongles/             # utils.c (request/release/can_take), free.c
  heap_queue/          # min-heap: init, add, pop, contains, align, free
  schedulers/          # get_key_fifo / get_key_edf
  mutex/               # getters.c, setters.c (thread-safe get/set helpers)
  parsing/             # parse.c, parse_validate.c, parse_utils.c
  logging/             # logging.c (ft_log_debug/info/warn/error)
  utils/               # mem.c (ft_calloc), free.c (free_all/free_return_int), str.c, time.c
```
