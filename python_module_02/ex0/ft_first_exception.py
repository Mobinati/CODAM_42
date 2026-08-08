def input_temperature(temp_str: str) -> int:
    print(f"Input data is '{temp_str}'")
    return (int(temp_str))


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


# if __name__ == "__main__":
#     print("=== Garden Temperature ===\n")
#     test_temperature()
#     print("All tests completed - program didn't crash!")
