*This project has been created as part of the 42 curriculum by mobina.*

# ft_printf

## Description

`ft_printf` is a small C library that reproduces the mandatory behaviour of
`printf` for the conversions `c`, `s`, `p`, `d`, `i`, `u`, `x`, `X`, and `%`.
It introduces variadic functions and writes output directly, without recreating
the buffering used by the standard-library implementation.

The resulting archive is named `libftprintf.a` and exposes this function:

```c
int ft_printf(const char *format, ...);
```

## Instructions

Build the library from the project root:

```sh
make
```

Include `ft_printf.h` in a C program and link the archive when compiling:

```sh
cc -Wall -Wextra -Werror main.c libftprintf.a -o example
./example
```

The available Makefile targets are `all`, `clean`, `fclean`, and `re`.

## Algorithm and data structures

`ft_printf` starts a `va_list` and scans the format string from left to right.
Ordinary characters are written immediately. When a percent sign is found, the
next character selects a conversion helper, which retrieves the argument with
the matching type and prints it. Every helper returns its number of written
characters, allowing the main loop to return the same total as `printf`.

Unsigned values are converted recursively. Each call divides the value by the
base length, prints the more significant digits first, and then writes the
current remainder. Decimal and hexadecimal output therefore share one helper
and differ only in their digit strings. Signed integers are promoted to `long`
before negation so that `INT_MIN` is handled safely. Pointers are converted
through `unsigned long` and prefixed with `0x`; a null pointer is written as
`(nil)`, matching the target libc.

No dynamic data structure or heap allocation is needed. The only state is the
format cursor, the `va_list`, counters, and the small call stack used by the
recursive number conversion. Output is sent directly through `write`.

## Resources

- `man 3 printf` — conversion behaviour and return values.
- `man 3 stdarg` — `va_start`, `va_arg`, and `va_end` usage.
- `man 2 write` — direct output and error handling.
- The 42 Norm — source formatting and function-size requirements.

AI was used to review the code, simplify some names and control flow, check
the project requirements, and suggest tests. The student remains responsible
for understanding the variadic arguments, conversions, and return-value
handling.
