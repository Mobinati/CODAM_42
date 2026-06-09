#!/bin/bash python3


array1 = [2, 8, 9, 48, 8, 22, -12, 2]
array2 = set()

for value in array1:
    new_value = value + 2
    array2.add(new_value)


print(array1)
print(array2)