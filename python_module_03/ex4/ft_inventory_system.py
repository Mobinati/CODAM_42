#!/usr/bin/env python3

import sys


def main() -> None:
    print("=== Inventory System Analysis ===")
    inventory: dict[str, int] = {}

    for arg in sys.argv[1:]:
        if ':' not in arg:
            print(f"Error - invalid parameter '{arg}'")
            continue
        parts = arg.split(":")
        if len(parts) != 2:
            print(f"Error - invalid parameter '{arg}'")
            continue

        item = parts[0]

        if item in inventory:
            print(f"Redundant item '{item}' - discarding")
            continue
        try:
            quantity = int(parts[1])
        except ValueError as e:
            print(f"Quantity error for '{item}': {e}")
            continue

        inventory[item] = quantity

    print(f"Got inventory: {inventory}")
    item_list = list(inventory.keys())
    print(f"Item list: {item_list}")
    total_value = sum(inventory.values())
    print(f"Total quantity of the 5 items: {total_value}")
    for item in item_list:
        percentage = round(inventory[item]/total_value * 100, 1)
        print(f"Item {item} represents {percentage}%")

    most_item = item_list[0]
    least_item = item_list[0]

    for item in item_list:
        if inventory[item] > inventory[most_item]:
            most_item = item
        if inventory[item] < inventory[least_item]:
            least_item = item

    print(f"Item most abundant: {most_item} "
          f"with quantity {inventory[most_item]}")
    print(f"Item least abundant: {least_item} "
          f"with quantity {inventory[least_item]}")

    inventory.update({"magic_item": 1})
    print(f"Updated inventory: {inventory}")


if __name__ == "__main__":
    main()
