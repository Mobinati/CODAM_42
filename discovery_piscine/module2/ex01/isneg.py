#!/bin/bash python3

NUM = input()
NUM = int(NUM)

if NUM == 0:
    print("This number is both positive and negative.")
elif (NUM > 0):
    print ("This number is positive.")
else:
    print("This number is negative.")