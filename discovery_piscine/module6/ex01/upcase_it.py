#!/bin/bash python3

import sys

if len(sys.argv) == 2:
    ARG = (sys.argv[1]).upper()
    print(ARG)
else:
    print("none")
