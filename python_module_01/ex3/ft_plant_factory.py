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

# def main():
#     print("=== Plant Factory Output ===")
#     plants = [
#         Plant("Rose", 25, 30, 0.8),
#         Plant("Oak", 200, 365, 0.3),
#         Plant("Cactus", 5, 90, 0.1),
#         Plant("Sunflower", 80, 45, 2.5),
#         Plant("Fern", 15, 120, 0.6)
#     ]
#     for plant in plants:
# 	    print("Created: ", end = '')
# 	    plant.show()
# if __name__ == "__main__":
# 	main()
