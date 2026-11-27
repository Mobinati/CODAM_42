*This project has been created as part of the 42 curriculum by mtousian.*

# Codexion

## Description

Codexion is a concurrent programming project written in C using POSIX threads (pthreads).

The project simulates several coders working at the same time. Each coder needs access to two shared dongles to compile. After compiling, they release the dongles and move on to debugging and refactoring before starting another cycle.

The main challenge is to manage shared resources safely while allowing multiple threads to work concurrently. The program also supports two scheduling policies, FIFO and EDF, and includes a cooldown period for dongles.

The goal is to build a simulation that handles concurrency correctly, avoids deadlocks, and detects when a coder has run out of time.

## Instructions

### Compilation

Clone the repository and enter the project directory:

```bash
git clone <repository-url>
cd Codexion
```

Compile the project:

```bash
make
```

To remove object files:

```bash
make clean
```

To remove object files and the executable:

```bash
make fclean
```

To recompile everything:

```bash
make re
```

### Execution

Run the program with the following arguments:

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor [number_of_required_compiles] dongle_cooldown scheduling_policy
```

The scheduling policy must be either `fifo` or `edf`.

Example:

```bash
./codexion 5 800 200 200 200 3 50 fifo
```

This starts a simulation with five coders. Each coder has 800 ms before burnout, needs 200 ms to compile, 200 ms to debug, and 200 ms to refactor. Each dongle has a cooldown of 50 ms, and the FIFO scheduler is used. Each coder must complete three compilations.

## Blocking cases handled

### Deadlock prevention

A deadlock can happen when several coders hold one dongle and wait for another one. To avoid this, the program uses a fixed resource order: a coder always requests the dongle with the smaller ID first.

This removes the circular-wait condition from the Coffman conditions, preventing deadlocks caused by coders holding resources while waiting for one another.

### Starvation and request scheduling

When several coders are waiting for the same dongle, their requests are handled by a priority queue.

- **FIFO:** requests are handled according to their arrival order.
- **EDF:** requests are ordered according to their deadlines.

These policies help organise access to shared dongles. They do not guarantee that starvation is impossible in every possible execution.

### Dongle cooldown

After a dongle is released, it cannot be used again until its cooldown period has passed.

The waiting coder is notified when the dongle becomes available. The availability check and request handling are protected by synchronization mechanisms so that two coders cannot claim the same dongle at the same time.

### Precise burnout detection

The simulation records the time when each coder starts compiling. The monitor checks how much time has passed since that point.

Shared state is protected with a mutex, so the monitor can read the relevant information safely while coder threads are running.

### Log serialization

Several coders may try to print messages at the same time. A logging mutex ensures that only one thread writes a message at a time.

This keeps the output readable and prevents messages from different threads from interfering with one another.

## Thread synchronization mechanisms

The project uses POSIX threading primitives to coordinate the coder threads, dongles, and monitor.

### `pthread_mutex_t`

Mutexes protect shared data and prevent multiple threads from modifying the same resource simultaneously.

They are used for:

- **Dongles:** each dongle has its own mutex to protect its availability and request queue.
- **Logging:** the logging mutex prevents messages from being printed simultaneously.
- **Simulation state:** the state mutex protects shared information such as the stop flag and coder progress.

For example, before changing shared simulation state, a thread locks the state mutex. It unlocks it after the update. This prevents another thread from reading or changing that data in the middle of the operation.

### `pthread_cond_t`

Condition variables allow threads to wait until something changes instead of continuously checking the same condition.

They are used for communication around dongle availability and simulation state.

For example, when a coder requests a dongle that is not available, it can wait on the dongle's condition variable. When the dongle becomes available again, another thread signals the condition variable.

The waiting thread then wakes up and checks the condition again before continuing.

### Request queue and scheduling

Each dongle has a request queue. The queue keeps track of coders waiting to use that dongle.

The queue is protected by the dongle mutex. This means that adding, removing, and checking requests cannot happen simultaneously from different threads.

The selected scheduling policy determines which waiting request gets priority.

### Communication between coders and the monitor

Coder threads update their progress and shared simulation state while holding the appropriate mutex.

The monitor reads that information using the same synchronization mechanism. This prevents race conditions between a coder updating its state and the monitor checking it.

When the simulation needs to stop, the stop flag is updated under the state mutex and the condition variable is broadcast. This allows waiting threads to be notified and finish their work safely.

## Resources

The following resources were useful for understanding the concepts used in this project:

- [POSIX Threads Programming](https://hpc-tutorials.llnl.gov/posix/) – an introduction to pthreads and thread synchronization.
- [Linux manual: pthread_mutex_lock](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html) – mutex locking and unlocking.
- [Linux manual: pthread_cond_wait](https://man7.org/linux/man-pages/man3/pthread_cond_wait.3p.html) – condition variables.
- [Linux manual: pthread_create](https://man7.org/linux/man-pages/man3/pthread_create.3.html) – creating threads.
- [The Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) – a classic example of deadlocks and shared-resource management.
- [Operating Systems: Three Easy Pieces](https://pages.cs.wisc.edu/~remzi/OSTEP/) – useful background on concurrency and scheduling.

### Use of AI

AI tools were used as a support during development, mainly to help understand concurrency concepts, discuss possible approaches to deadlock prevention and scheduling, and review parts of the implementation.

They were also used to help with explanations and README documentation. The project code was developed and tested as part of the learning process, with attention to understanding how the different threads and synchronization mechanisms work.