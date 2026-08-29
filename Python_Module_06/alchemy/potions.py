# relative → alchemy/elements.py
from . import elements
# absolute → root elements.py
import elements as elm


def healing_potion() -> str:
    str2 = elements.create_earth()
    str3 = elements.create_air()
    return (f"Healing potion brewed with '{str2}' and '{str3}'")


def strength_potion() -> str:
    str2 = elm.create_fire()
    str3 = elm.create_water()
    return (f"Strength potion brewed with '{str2}' and '{str3}'")
