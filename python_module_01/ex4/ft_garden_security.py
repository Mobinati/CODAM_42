class Plant:
    def __init__(self, name: str, height: float, age: int) -> None:
        self._name = name
        self._height = height
        self._age = age
        print(f"Plant created: {self._name}: "
              f"{self._height:.1f}cm, {self._age} days old\n")

    def set_height(self, height: float) -> None:
        if height < 0:
            print(f"{self._name}: Error, height can't be negative")
            print("Height update rejected")
        else:
            self._height = float(height)
            print(f"Height updated: {self._height}cm")

    def set_age(self, age: int) -> None:
        if age < 0:
            print(f"{self._name}: Error, age can't be negative")
            print("Age update rejected")
        else:
            self._age = int(age)
            print(f"Age updated: {self._age} days")

    def get_height(self) -> float:
        return (self._height)

    def get_age(self) -> int:
        return (self._age)

    def show(self) -> None:
        print(f"Current state: {self._name}: "
              f"{self._height:.1f}cm, {self._age} days old")

# def main():
#     print("=== Garden Security System ===")

#     rose = Plant("Rose", 15, 10)
#     rose.set_height(25)
#     rose.set_age(30)
#     print('\n')
#     rose.set_height(-25)
#     rose.set_age(-30)
#     print('\n')
#     rose.show()
# if __name__ == "__main__":
# 	main()
