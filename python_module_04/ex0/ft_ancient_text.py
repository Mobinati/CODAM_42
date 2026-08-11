#!/usr/bin/env python3

import sys


def main():
    if len(sys.argv[1:]) < 1:
        print(f"Usage: {sys.argv[0]} <file>")
        return

    print("=== Cyber Archives Recovery ===")

    file = sys.argv[1]
    print(f"Accessing file '{file}'")
    try:
        f = open(file)
        print("---\n")
        print(f.read())
        print("\n---")
        f.close()
        print(f"File '{file}' closed")
    except Exception as e:
        print(f"Error opening file '{file}': {e}")


if __name__ == "__main__":
    main()
