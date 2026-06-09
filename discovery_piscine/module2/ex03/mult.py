#!/bin/bash python3

N1 = int(input("Enter the first number:"))
N2 = int(input("Enter the second number:"))
MULT = N1 * N2

print(f"{N1} x {N2} = {MULT}")

if MULT == 0:
    print("The result is both positive and negative.")
elif (MULT > 0):
    print ("The result is positive.")
else:
    print("The result is negative.")