
class GardenError(Exception):
    def __init__(self, message: str = "Unknown garden error") -> None:
        super().__init__(message)


class PlantError(GardenError):
    def __init__(self, message: str = "Unknown plant error") -> None:
        super().__init__(message)


def water_plant(plant_name: str) -> None:
    if plant_name[0].isupper():
        print(f"Watering {plant_name} : [OK]")
    else:
        raise PlantError(
            f"Invalid plant name to water: '{plant_name}'"
        )


def test_watering_system(plant_list: list[str]) -> None:
    print("Opening watering system")
    try:
        for plant in plant_list:
            water_plant(plant)

    except PlantError as e:
        print(f"Caught PlantError: {e}")
        print(".. ending tests and returning to main")
        return
    finally:
        print("Closing watering system\n")


# if __name__ == "__main__":
#     print("=== Garden Watering System ===\n")

#     print("Testing valid plants...")
#     test_watering_system(["Tomato", "Lettuce", "Carrots"])

#     print("\nTesting invalid plants...")
#     test_watering_system(["Tomato", "lettuce", "Carrots"])

#     print("\nCleanup always happens, even with errors!")
