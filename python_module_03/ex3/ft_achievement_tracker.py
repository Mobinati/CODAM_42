#!/usr/bin/env python3

import random

achievements = [
    "Inception",
    "Interstellar",
    "The Matrix",
    "Gladiator",
    "The Godfather",
    "Pulp Fiction",
    "Fight Club",
    "The Dark Knight",
    "Forrest Gump",
    "The Prestige",
    "Whiplash",
    "Parasite",
    "Arrival",
    "The Departed",
    "Memento",
    "Dune",
    "Oppenheimer",
    "lord of the rings",
    "Mad Max: Fury Road",
    "Spider-Man"
]


def gen_player_achievements() -> set[str]:
    number = random.randint(7, 14)
    selected = random.sample(achievements, number)
    return (set(selected))


def main() -> None:
    print("=== Achievement Tracker System ===\n")
    Mobina = gen_player_achievements()
    print(f"Player Mobina: {Mobina}\n")
    Adel = gen_player_achievements()
    print(f"Player Adel: {Adel}\n")
    Aram = gen_player_achievements()
    print(f"Player Aram: {Aram}\n")
    Morvarid = gen_player_achievements()
    print(f"Player Morvarid: {Morvarid}\n")
    Towhid = gen_player_achievements()
    print(f"Player Towhid: {Towhid}\n")
    print(f"All distinct achievements: "
          f"{Mobina | Adel | Aram | Morvarid | Towhid}\n")
    print(f"Common achievements: {Mobina & Adel & Aram & Morvarid & Towhid}\n")
    print(f"Only Mobina has: "
          f"{Mobina.difference(Adel, Aram, Morvarid, Towhid)}")
    print(f"Only Adel has: {Adel.difference(Mobina, Aram, Morvarid, Towhid)}")
    print(f"Only Aram has: {Aram.difference(Mobina, Adel, Morvarid, Towhid)}")
    print(f"Only Morvarid has: "
          f"{Morvarid.difference(Mobina, Adel, Aram, Towhid)}")
    print(f"Only Towhid has: "
          f"{Towhid.difference(Mobina, Adel, Aram, Morvarid)}\n")
    print(f"Mobina is missing: {set(achievements) - Mobina}")
    print(f"Adel is missing: {set(achievements) - Adel}")
    print(f"Aram is missing: {set(achievements) - Aram}")
    print(f"Morvarid is missing: {set(achievements) - Morvarid}")
    print(f"Towhid is missing: {set(achievements) - Towhid}")


if __name__ == "__main__":
    main()
