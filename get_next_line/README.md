*This project has been created as part of the 42 curriculum by <mtousian>.*

# get_next_line

## Description

`get_next_line` implements `char *get_next_line(int fd)`, a function that reads
one line at a time from a file descriptor. Each returned line includes its trailing
newline when one exists. It works with regular files and standard input, and returns
`NULL` at end-of-file or on error.

## Instructions

Compile the mandatory files with the usual 42 flags. `BUFFER_SIZE` controls the
number of bytes requested from `read` at a time and defaults to `42` when omitted.

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
  get_next_line.c get_next_line_utils.c your_main.c
```

Call `get_next_line(fd)` repeatedly and `free` every non-NULL result returned.

## Algorithm and technical choices

The function keeps unread characters in a function-local static `stash`, which
persists between calls without using a global variable. On each call it first checks
the stash for a newline. If absent, it reads only `BUFFER_SIZE` bytes at a time and
appends them until a newline or end-of-file is reached. It then returns the prefix
through the newline and retains the remaining suffix for the next call. At EOF, the
remaining unterminated text is returned once. This avoids reading the whole file at
once and works for any positive buffer size.

The mandatory implementation maintains one stash, so it is intended for one active
file descriptor at a time. Memory is released on read errors and allocation failures.

## Resources

- [read(2) — Linux manual page](https://man7.org/linux/man-pages/man2/read.2.html)
- [C dynamic-memory allocation — cppreference](https://en.cppreference.com/w/c/memory/malloc)
- 42 get_next_line subject PDF (provided with the project)

AI was used to help draft the initial implementation, README structure, and local
compile tests. The algorithm and resulting code were reviewed against the project
requirements.
