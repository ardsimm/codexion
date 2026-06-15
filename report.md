# Codexion — Compliance & Bug Report

Review of the codebase against `pdf/en.subject.pdf` (v1.4).
Date: 2026-06-15. Branch: `chore/vogsphere`.

## Summary

The project is **substantially compliant**. It builds clean with the mandatory
flags, uses only authorized functions, has no global variables, implements a
custom heap-based priority queue, logs in the required format, and passes a
valgrind leak check. The issues below are ordered by severity.

---

## Confirmed compliant (verified)

- Builds clean with `cc -Wall -Wextra -Werror -pthread`; `make` / `all` / `re`
  work and a second `make` performs no unnecessary relinking.
- Only authorized external functions are used (pthread_*, gettimeofday, usleep,
  malloc/free, printf/fprintf, strcmp/strlen, memset). No libft, no forbidden calls.
- No global variables.
- Custom heap priority queue (no stdlib container); FIFO and EDF keys match the
  spec, with coder-ID tie-breaking.
- Log format matches exactly (`<ms> <id> <message>`, two "has taken a dongle"
  before "is compiling"), serialized under `logging_mutex`.
- Topology correct: N coders, N dongles, circular wrap, heap `max_size = 2`
  matches the 2 coders per dongle.
- `ms -> us` conversion (`convert_ms_to_us`) keeps timing internally consistent.
- Cooldown enforced; burnout detected by polling every 10 us (well within the
  10 ms requirement).
- Invalid arguments rejected (missing/extra args, negatives, non-integers, bad
  scheduler, 0 coders).
- No memory leaks (valgrind `--leak-check=full` clean); short helgrind run
  reported no races.

---

## Defects to fix before defense

### 1. README first line is malformed — HIGH
`README.md:1` is duplicated/garbled:
`*This project has been created as part of the 42 curriculum by sm*This project has been created ... by smenard.*`
The subject requires that exact italicized line as the very first line.
Evaluators check this explicitly.

### 2. Makefile typo `$(CLFAGS)` — MEDIUM
`Makefile:158` and `Makefile:164` reference the undefined variable `CLFAGS`
(should be `CFLAGS`). The `debug` and `vg` targets therefore build **without**
`-Wall -Wextra -Werror -pthread`. The mandatory `make` / `re` path is fine, but
these documented helper targets are broken, and missing `-pthread` can fail to
link on some systems.

### 3. Monitor runs in the main thread, not a spawned thread — MEDIUM (interpretation)
The subject says "a separate **monitor thread**". `monitor_simulation()` polls
from the `main` thread while coders run as threads. Functionally separate and
commonly accepted, but a strict evaluator may expect a dedicated `pthread`.
Confirm against the evaluation sheet.

---

## Potential bugs

### 4. Spurious post-shutdown "compile" path — `src/coders/tasks.c`
If `run` flips to `false` while a coder waits inside `take_dongles()`, that
function returns **without having acquired the dongles**, yet `compile()` then
sets `last_compile_timestamp`, logs "is compiling", sleeps, and "releases"
dongles it never took. Currently masked because INFO logs are suppressed once
`run == false`, but it is logically unsound (timestamps/releases on un-acquired
dongles).

### 5. `hq_init` element-size mismatch — `src/init/dongles.c` -> `src/heap_queue/init.c`
The data buffer is allocated as `sizeof(t_coder)` per slot but indexed as
`t_heap_queue_item`. Safe today only because `t_coder` is larger; it is the
wrong size constant and becomes a heap overflow if the relative struct sizes
ever invert.

### 6. Unguarded `hq->data[0]` peek — `src/dongles/utils.c` (`can_take_dongle`)
No `size > 0` guard before reading `data[0]`. Safe in the current flow (caller
always enqueues itself first, so size >= 1), but would read stale/garbage memory
if ever called on an empty queue.

### 7. Data race on `last_compile_timestamp` under EDF — `src/schedulers/schedulers.c`
Written under `coder->mutex` but read in `get_key_edf()` while holding the
*dongle* mutex (not the coder mutex). Benign word-sized race, but a genuine race
helgrind can flag on EDF runs.

### 8. Incomplete mutex cleanup
Only dongle mutexes are destroyed. Coder mutexes and
`shared.mutex` / `logging_mutex` / `start` are never `pthread_mutex_destroy`'d,
and the `init` error paths skip destroying already-initialized mutexes. Not a
memcheck leak (embedded in freed structs), but incomplete teardown.

### 9. `uint32_t` overflow in `convert_ms_to_us` — `src/parsing/parse.c`
Time arguments are `uint32_t`; `*= 1000` overflows for inputs above ~4.29M ms.
Unrealistic, but unvalidated.

---

## Minor doc / wording inconsistencies

### 10. Misleading 0-coder message — `src/main.c`
Rejects 0 coders with "less than 2 coders" even though 1 coder is accepted (it
correctly burns out). Wording should match the actual boundary.

### 11. README stagger description mismatch
README says odd-ID coders wait "half the compile duration", but the code sleeps
the **full** `time_to_compile` (`src/coders/routine.c`).

### 12. README claims condition variables are used
The intro mentions "condition variables", but the implementation uses none
(busy-wait polling at 10 us). The subject's README spec asks to describe
`pthread_cond_t` / custom events — either reflect the polling design accurately
or state that condition variables were intentionally not used.

---

## Notes

- Items 1 and 2 are the only ones that would clearly cost points; item 3 is an
  interpretation worth confirming.
- Items 4-9 are correctness/robustness issues that do not break the verified runs.
- `compile_commands.json` is tracked in git but is harmless (not a violation).
