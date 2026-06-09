#!/bin/bash python3

import sys

if len(sys.argv) == 2:
    ARG = (sys.argv[1]).lower()
    print(ARG)
else:
    print("none")
