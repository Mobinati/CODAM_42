class Plant:
    def __init__(
        self,
        name: str,
        height: float,
        age: int,
        growth_rate: float
    ) -> None:
        self.name = name
        self.height = height
        self.age = age
        self.growth_rate = growth_rate

    def grow(self) -> None:
        self.height += self.growth_rate

    def plant_age(self) -> None:
        self.age += 1

    def show(self) -> None:
        print(f"{self.name}: {self.height:.1f}cm, {self.age} days old")

# def	main():
# 	print("=== Garden Plant Growth ===")
# 	rose = Plant("Rose", 25, 30, 0.8)
# 	start_height = rose.height
# 	rose.show()

# 	for day in range (1 , 8):
# 		print(f"=== Day {day} ===")
# 		rose.grow()
# 		rose.plant_age()
# 		rose.show()
# 	print(f"Growth this week: {round(rose.height - start_height, 1)}cm")

# if __name__ == "__main__":
# 	main()
