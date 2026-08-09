class Plant:

    class Statistics:
        def __init__(self) -> None:
            self._grow_calls = 0
            self._age_calls = 0
            self._show_calls = 0

        def grow_called(self) -> None:
            self._grow_calls += 1

        def age_called(self) -> None:
            self._age_calls += 1

        def show_called(self) -> None:
            self._show_calls += 1

    def __init__(
        self,
        name: str,
        height: float,
        age: int,
        growth_rate: float
    ) -> None:
        self._name = name
        self._height = height
        self._age = age
        self._growth_rate = growth_rate
        self._stats = Plant.Statistics()

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

    @staticmethod
    def check_age(age: int) -> bool:
        return (age > 365)

    @classmethod
    def create_anonymous(cls) -> "Plant":
        return cls("Unknown plant", 0.0, 0, 0.0)

    def age(self) -> None:
        self._age += 1
        self._stats.age_called()

    def grow(self) -> None:
        self._height += self._growth_rate
        self._stats.grow_called()

    def show(self) -> None:
        print(f"{self._name}: {self._height:.1f}cm, {self._age} days old")
        self._stats.show_called()


class Flower(Plant):
    def __init__(
        self,
        name: str,
        height: float,
        age: int,
        growth_rate: float,
        color: str
    ) -> None:
        super().__init__(name, height, age, growth_rate)
        self.color = color
        self.bloomed = False

    def bloom(self) -> None:
        self.bloomed = True

    def show(self) -> None:
        super().show()
        print(f"Color: {self.color}")
        if self.bloomed:
            print(f"{self._name} is blooming beautifully!")
        else:
            print(f"{self._name} has not bloomed yet")


class Seed(Flower):
    def __init__(
        self,
        name: str,
        height: float,
        age: int,
        growth_rate: float,
        color: str
    ) -> None:
        super().__init__(name, height, age, growth_rate, color)
        self._seeds = 0

    def bloom(self) -> None:
        super().bloom()
        if self.bloomed:
            self._seeds = 42

    def age(self) -> None:
        self._age += 20
        self._stats.age_called()

    def show(self) -> None:
        super().show()
        if self.bloomed:
            print(f"Seeds: {self._seeds}")
        else:
            print("Seeds: 0")


class Tree(Plant):
    def __init__(
        self,
        name: str,
        height: float,
        age: int,
        growth_rate: float,
        trunk_diameter: float
    ) -> None:
        super().__init__(name, height, age, growth_rate)
        self._trunk_diameter = trunk_diameter
        self._shade_calls = 0

    def show(self) -> None:
        super().show()
        print(f"Trunk diameter: {self._trunk_diameter}cm")

    def produce_shade(self) -> None:
        print(f"Tree {self._name} now produces a shade of "
              f"{self._height}cm long and {self._trunk_diameter}cm wide.")
        self.shade_called()

    def shade_called(self) -> None:
        self._shade_calls += 1


class Vegetable(Plant):
    def __init__(
        self,
        name: str,
        height: float,
        age: int,
        growth_rate: float,
        harvest_season: str,
    ) -> None:

        super().__init__(name, height, age, growth_rate)
        self._harvest_season = harvest_season
        self._nutritional_value = 0

    def age(self) -> None:
        super().age()
        self._nutritional_value += 1

    def show(self) -> None:
        super().show()
        print(f"Harvest season: {self._harvest_season}")
        print(f"Nutritional value: {self._nutritional_value}")

    def grow(self) -> None:
        super().grow()
        self._nutritional_value += 1


def display_statistics(plant: Plant) -> None:
    print(f"Stats: {plant._stats._grow_calls} grow, "
          f"{plant._stats._age_calls} age, "
          f"{plant._stats._show_calls} show"
          )
    if isinstance(plant, Tree):
        print(f"{plant._shade_calls} shade")

# def main():
#     print("=== Garden statistics ===")

#     print("=== Check year-old")
#     print(
#         f"Is 30 days more than a year? -> "
#         f"{Plant.check_age(30)}"
#     )
#     print(
#         f"Is 400 days more than a year? -> "
#         f"{Plant.check_age(400)}"
#     )
#     print()
#     print("=== Flower")
#     rose = Flower("Rose", 15, 10, 8.0, "red")
#     rose.show()
#     display_statistics(rose)

#     # print("[asking the rose to grow and bloom]")
#     rose.grow()
#     rose.bloom()
#     rose.show()
#     display_statistics(rose)
#     print()
#     print("=== Tree")
#     oak = Tree("Oak", 200, 365, 0.0, 5)
#     oak.show()
#     display_statistics(oak)

#     # print("[asking the oak to produce shade]")
#     oak.produce_shade()
#     display_statistics(oak)

#     print()
#     print("=== Seed")
#     sunflower = Seed("Sunflower", 80, 45, 30.0, "yellow")
#     sunflower.show()

#     sunflower.grow()
#     sunflower.age()
#     sunflower.bloom()
#     sunflower.show()
#     display_statistics(sunflower)
#     print()
#     print("=== Anonymous")
#     anonymous = Plant.create_anonymous()
#     anonymous.show()
#     display_statistics(anonymous)


# if __name__ == "__main__":
#     main()
