def garden_operations(op_n: int) -> None:
    if op_n == 0:
        int("abc")
    elif op_n == 1:
        10 / 0
    elif op_n == 2:
        open('non/existing/dress')
    elif op_n == 3:
        "mobina" + 42
    else:
        return


def test_error_types() -> None:
    for i in range(5):
        print(f"Testing operation {i}...")
        try:
            garden_operations(i)
            print("Operation completed successfully\n")
        except ValueError as e:
            print(f"Caught ValueError: {e}")

        except ZeroDivisionError as e:
            print(f"Caught ZeroDivisionError: {e}")

        except FileNotFoundError as e:
            print(f"Caught FileNotFoundError: {e}")

        except TypeError as e:
            print(f"Caught TypeError: {e}")
    print("All error types tested successfully!")


# if __name__ == "__main__":
#     test_error_types()
