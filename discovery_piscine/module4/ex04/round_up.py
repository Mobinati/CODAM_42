#!/bin/bash python3

num = input("Give me a number:")

float_num = float(num)
integer_num = int(float_num)

if num.isdigit():
    print(num)
else:
    print(integer_num + 1)