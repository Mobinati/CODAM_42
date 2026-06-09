#!/bin/bash python3

INT = int(input("Enter a number less than 25\n"))

if INT > 25:
    print("Error")
else:
    while INT <= 25:
        print(f"Inside the loop, my variable is {INT}" )
        INT += 1