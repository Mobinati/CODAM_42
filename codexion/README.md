*This project has been created as part of the 42 curriculum by Mobinati.*

## Description

Codexion is a C concurrency simulation. Each coder is a thread. Coders share USB dongles arranged in a circle. A coder needs two neighbouring dongles to compile, then spends time debugging and refactoring.

The program demonstrates thread synchronization, resource sharing, cooldowns, FIFO and EDF scheduling, and burnout detection.

## Instructions

Compile:

```sh
make
```

Run:

```sh
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown fifo
```

Use `edf` instead of `fifo` to select Earliest Deadline First scheduling. All times are in milliseconds.

Clean:

```sh
make fclean
```

## Blocking cases handled

- A single mutex protects shared simulation state and dongle ownership.
- A coder is granted both required dongles together, so it cannot hold one while waiting for the other.
- The scheduler uses a heap to order requests by FIFO arrival order or EDF deadline.
- Dongles are unavailable until their cooldown has passed.
- The monitor checks burnout deadlines and stops the simulation.
- All output is printed while the shared mutex is locked, preventing mixed log lines.

## Thread synchronization mechanisms

The program uses `pthread_create` and `pthread_join` for coder and monitor threads. A shared `pthread_mutex_t` protects the scheduler, dongle states, coder counters, and stop flag. A `pthread_cond_t` wakes threads when resources change or the simulation stops. Timed condition waits allow coders to wait for phase durations and allow the monitor to wake at a burnout deadline.

## Resources

- The POSIX Threads documentation: https://man7.org/linux/man-pages/man7/pthreads.7.html
- `gettimeofday`: https://man7.org/linux/man-pages/man2/gettimeofday.2.html
- AI was used to help draft and review the project structure and implementation. The code must be checked, tested, and understood by the student before submission.
