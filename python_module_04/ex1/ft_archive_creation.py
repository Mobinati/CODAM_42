#!/usr/bin/env python3

import sys
import typing


def main():
    if len(sys.argv[1:]) < 1:
        print(f"Usage: {sys.argv[0]} <file>")
        return

    print("=== Cyber Archives Recovery & Preservation ===")

    file = sys.argv[1]
    print(f"Accessing file '{file}'")
    try:
        f: typing.IO = open(file)
        content = f.read()
        print("---\n")
        print(content)
        print("\n---")
        f.close()
        print(f"File '{file}' closed")
        print("Transform data:")
        print("---")
        new_content = ""
        i = 0
        while i < len(content):
            if content[i] == "\n":
                new_content += "#\n"
            else:
                new_content += content[i]
            i += 1

        if len(content) > 0 and content[(len(content)-1)] != "\n":
            new_content += "#\n"

        print(new_content, end="")
        print("---")

        file_name = input("Enter new file name (or empty):")

        if file_name:
            new_file = open(file_name, "w")
            new_file.write(new_content)
            new_file.close()
            print(f"Saving data to '{file_name}'")
            print(f"Data saved in file '{file_name}'.")

        else:
            print("Not saving data.")

    except Exception as e:
        print(f"Error opening file '{file}': {e}")


if __name__ == "__main__":
    main()
