*This project has been created as part of the 42 curriculum by <mtousian@student.codam.nl>*

# Libft

## Description

Libft is the first project in the 42 core curriculum. Its goal is to recreate a subset of standard C library functions and extend them with additional utilities.

This project focuses on understanding fundamental programming concepts such as memory management, string manipulation, and low-level operations. The result is a static library (`libft.a`) that can be reused in future projects as a personal toolbox.

---

## Instructions

Clone the repository and compile the library:

bash
git clone <your-repo-url>
cd libft
make


Makefile Rules

Command	Description:
make
make clean	Remove object files
make fclean	Remove object files and library
make re	Recompile everything

---

## Resources

Documentation
The C Programming Language — Kernighan & Ritchie
GNU C Library Documentation
POSIX Standard
42 Subject
Testing
libft-unit-test (community tester)
Custom test files
AI tools (such as ChatGPT) were used for:Explaining complex concepts (memory allocation, pointers)


All code was implemented and validated manually.


Usage

Include the header file:

#include "libft.h"

Compile with:

gcc main.c program


Library Details

Part 1 — Libc Functions

Part 1 — Reimplemented C Library Functions

ft_isalpha – Checks if a character is an alphabetic letter (A–Z or a–z).

ft_isdigit – Checks if a character is a numeric digit (0–9).

ft_isalnum – Checks if a character is alphanumeric (letter or digit).

ft_isascii – Checks if a character is within the ASCII range (0–127).

ft_isprint – Checks if a character is printable (including space).

ft_strlen – Returns the length of a string (excluding null terminator).

ft_memset – Fills a block of memory with a specified byte value.

ft_bzero – Sets a block of memory to zero.

ft_memcpy – Copies a block of memory from source to destination (no overlap handling).

ft_memmove – Copies memory safely, handling overlapping regions.

ft_strlcpy – Copies a string with size limit and guarantees null-termination.

ft_strlcat – Concatenates strings with size limit and null-termination.

ft_toupper – Converts a lowercase letter to uppercase.

ft_tolower – Converts an uppercase letter to lowercase.

ft_strchr – Finds the first occurrence of a character in a string.

ft_strrchr – Finds the last occurrence of a character in a string.

ft_strncmp – Compares two strings up to a specified number of characters.

ft_memchr – Searches for a byte in a block of memory.

ft_strnstr – Locates a substring within a string up to a given length.

ft_atoi – Converts a string to an integer.

ft_calloc – Allocates memory and initializes it to zero.

ft_strdup – Creates a duplicate of a string in newly allocated memory.

Part 2 — Additional Functions
ft_substr – Extracts a substring from a string given start and length.

ft_strjoin – Concatenates two strings into a new string.

ft_strtrim – Removes specified characters from the beginning and end of a string.

ft_split – Splits a string into an array of substrings based on a delimiter.

ft_itoa – Converts an integer to a string.

ft_strmapi – Applies a function to each character of a string to create a new string.

ft_striteri – Applies a function to each character of a string in-place.

ft_putchar_fd – Writes a character to a file descriptor.

ft_putstr_fd – Writes a string to a file descriptor.

ft_putendl_fd – Writes a string followed by a newline to a file descriptor.

ft_putnbr_fd – Writes an integer to a file descriptor.

Bonus Part — Linked List Functions
ft_lstnew – Creates a new list node with given content.

ft_lstadd_front – Adds a node at the beginning of a list.

ft_lstsize – Counts the number of nodes in a list.

ft_lstlast – Returns the last node of a list.

ft_lstadd_back – Adds a node at the end of a list.

ft_lstdelone – Deletes a single node using a provided function.

ft_lstclear – Deletes and frees all nodes in a list.

ft_lstiter – Applies a function to each node’s content.

ft_lstmap – Creates a new list by applying a function to each node’s content.

#note:
All functions are prefixed with ft_
No global variables are used
Helper functions are declared static
Focus on robustness and memory safety
Fully compliant with the 42 Norm

Example
#include "libft.h"

int main(void)
{
    char *str = ft_split("Hello World", ' ');
    
}
Notes
This project builds a strong foundation for future 42 projects
and improves understanding of core programming concepts for standard functions

Author

<Mobina tousian>
