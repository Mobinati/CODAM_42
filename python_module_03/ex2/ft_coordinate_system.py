#!/usr/bin/env python3

import math


def get_player_pos() -> tuple[float, float, float]:
    while True:
        coords = input("Enter new coordinates as floats in format 'x,y,z':")
        try:
            x_str, y_str, z_str = coords.split(",")

            x = float(x_str)
            y = float(y_str)
            z = float(z_str)

            return (x, y, z)

        except ValueError as e:
            if "," not in coords or len(coords.split(",")) != 3:
                print("Invalid syntax\n")
            else:
                print(e)


if __name__ == "__main__":
    print("=== Game Coordinate System ===\n")
    print("Get a first set of coordinates")
    first = get_player_pos()
    print(f"Got a first tuple: {first}")
    print(f"It includes: X={first[0]}, Y={first[1]}, Z={first[2]}")
    dist = first[0]**2 + first[1]**2 + first[2]**2
    print(f"Distance to center: {(math.sqrt(dist)):.4f}")
    print("\nGet a second set of coordinates")
    second = get_player_pos()
    X = (second[0]-first[0])**2
    Y = (second[1]-first[1])**2
    Z = (second[2]-first[2])**2
    dist2 = math.sqrt(X + Y + Z)
    print(f"Distance between the 2 sets of coordinates: {(dist2):.4f}")
