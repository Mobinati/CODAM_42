def input_temperature(temp_str: str) -> int:
    print(f"Input data is '{temp_str}'")

    temp = int(temp_str)
    if (temp < 0):
        raise ValueError(f"{temp}°C is too cold for plants (max 40°C)")
    elif (temp > 41):
        raise ValueError(f"{temp}°C is too hot for plants (max 40°C)")
    return (temp)


def test_temperature() -> None:
    # temp_str = input("Give the temp: ")
    try:
        temp = input_temperature("25")
        print(f"Temperature is now {temp}°C")
    except ValueError as e:
        print(f"Caught input_temperature error: {e}\n")
    print()
    try:
        temp = input_temperature("abc")
        print(f"Temperature is now {temp}°C")
    except ValueError as e:
        print(f"Caught input_temperature error: {e}\n")
    print()
    try:
        temp = input_temperature("100")
        print(f"Temperature is now {temp}°C")
    except ValueError as e:
        print(f"Caught input_temperature error: {e}\n")
    print()
    try:
        temp = input_temperature("-50")
        print(f"Temperature is now {temp}°C")
    except ValueError as e:
        print(f"Caught input_temperature error: {e}\n")

# if __name__ == "__main__":
#     print("=== Garden Temperature Checker ===\n")
#     test_temperature()
#     print("All tests completed - program didn't crash!")
