#!/bin/bash python3


array1 = [1, 3, 6, 7, 77, -20, 0]
array2 = array1.copy()
i = 0
while i < len(array1):
    array2[i] = array1[i] + 2
    i +=1

print(array1)
print(array2)