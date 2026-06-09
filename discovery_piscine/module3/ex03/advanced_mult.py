#!/bin/bash python3
a = 0
b = 0

while (a <= 10):
    print (f"Table of {a} :", end = " ")
    while (b <= 10):
        mult = a * b
        print (mult, end = " ")
        b +=1
    a +=1
    b = 0
    print()