#!/bin/bash python3

import math
N1 = float(input("Give me a number:"))


if N1.is_integer():
    print("This number is an integer.")
else:
    print("This number is a decimal.")