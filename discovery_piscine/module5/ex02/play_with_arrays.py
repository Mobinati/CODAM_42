#!/bin/bash python3


array1 = [1, 3, 6, 7, 77, -20, 0]
array2 = []
i = 0
while i < len(array1):
    if array1[i] > 5:
        array2.append(array1[i])
    i +=1

print(array1)
print(array2)