#!/bin/bash python3

nmbr = int(input("Enter a number\n"))
a = 0
while a < 10:
    print(f"{a} x {nmbr} = {nmbr*a}")
    a += 1