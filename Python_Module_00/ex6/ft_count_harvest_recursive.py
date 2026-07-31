def ft_count_harvest_recursive() -> None:
    days = int(input("Days until harvest: "))

    def count_days_down(day: int) -> None:
        if day > days:
            print("Harvest time!")
            return
        print("Day", day)
        count_days_down(day + 1)
    count_days_down(1)
