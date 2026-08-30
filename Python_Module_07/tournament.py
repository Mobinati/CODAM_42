from ex0 import FlameFactory, AquaFactory
from ex1 import HealingCreatureFactory, TransformCreatureFactory
from ex2 import NormalStrategy, AggressiveStrategy, DefensiveStrategy


def battle(opponents):
    print("*** Tournament ***")
    print(f"{len(opponents)} opponents involved")

    for first in range(len(opponents)):
        for second in range(first + 1, len(opponents)):

            factory1 = opponents[first][0]
            strategy1 = opponents[first][1]

            factory2 = opponents[second][0]
            strategy2 = opponents[second][1]

            creature1 = factory1.create_base()
            creature2 = factory2.create_base()

            print("* Battle *")
            print(creature1.describe())
            print("vs.")
            print(creature2.describe())
            print("now fight!")

            try:
                strategy1.act(creature1)
                strategy2.act(creature2)

            except TypeError as error:
                print(f"Battle error, aborting tournament: {error}")
                return


def main():
    normal = NormalStrategy()
    aggressive = AggressiveStrategy()
    defensive = DefensiveStrategy()

    flame = FlameFactory()
    healing = HealingCreatureFactory()
    transforming = TransformCreatureFactory()

    print("Tournament 0 (basic)")

    opponents = [
        (flame, normal),
        (healing, defensive)
    ]

    battle(opponents)

    print("Tournament 1 (error)")

    opponents = [
        (flame, aggressive),
        (healing, defensive)
    ]

    battle(opponents)

    print("Tournament 2 (multiple)")

    opponents = [
        (AquaFactory(), normal),
        (healing, defensive),
        (transforming, aggressive)
    ]

    battle(opponents)


if __name__ == "__main__":
    main()
