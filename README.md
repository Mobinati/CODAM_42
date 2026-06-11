# push_swap

## 📌 Description

**push_swap** is a sorting algorithm project from 42/Codam.

The goal is to sort a stack of integers using a limited set of operations and the lowest possible number of moves.

You are given two stacks:
- **stack A** (initially contains unsorted integers)
- **stack B** (initially empty)

You must sort stack A in ascending order using only allowed operations.

---

## ⚙️ Allowed operations

- `sa` : swap the first two elements of stack A  
- `sb` : swap the first two elements of stack B  
- `ss` : `sa` and `sb` at the same time  

- `pa` : push top of B to A  
- `pb` : push top of A to B  

- `ra` : rotate A up  
- `rb` : rotate B up  
- `rr` : `ra` and `rb`  

- `rra` : reverse rotate A  
- `rrb` : reverse rotate B  
- `rrr` : `rra` and `rrb`

---

## 🧠 Algorithm

This implementation uses:

- Index normalization (mapping values to sorted positions)
- Small sort optimization for 2–5 numbers
- Radix sort (binary sorting) for larger inputs

### Complexity:
- Small input: optimized manual sorting
- Large input: O(n * log n)

---

## 🏗️ Project structure
.
├── main.c
├── push_swap.h
├── parse.c
├── sort.c
├── Makefile
└── stack/
├── stack_init.c
└── stack_utils.c



---

## 🚀 How to compile

```bash
make

./push_swap 3 2 1

Example output:
sa
rra
If you have a checker program:

ARG="3 2 1"
./push_swap $ARG | ./checker_linux $ARG

Expected result:

OK
