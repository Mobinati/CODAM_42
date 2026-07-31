def ft_water_reminder() -> None:
    data = int(input('Days since last watering: '))
    if data > 2:
        print("Water the plants!")
    else:
        print("Plants are fine")
