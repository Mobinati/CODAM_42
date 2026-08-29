import elements as elm
from .. import elements
from .. import potions


def lead_to_gold() -> str:
    return (f"Recipe transmuting Lead to Gold: "
            f"brew ’{elements.create_air()}'"
            f" and ’{potions.strength_potion()}’ "
            f"mixed with ’{elm.create_fire()}’")
