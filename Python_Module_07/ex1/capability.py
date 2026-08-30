from abc import ABC, abstractmethod
from ex0.factory import CreatureFactory
from ex0.creature import Creature


class HealCapability(ABC):
    @abstractmethod
    def heal() -> str:
        pass

class TransformCapability(ABC):
    @abstractmethod
    def transform(self) -> str:
        pass

    @abstractmethod
    def revert(self) -> str:
        pass

class Sproutling(HealCapability, Creature):
    def attack(self) -> str:
        return ("Sproutling uses Vine Whip!")
    
    def heal(self) -> str:
        return ("Sproutling heals itself for a small amount")



class Bloomelle(HealCapability, Creature):
    def attack(self) -> str:
        return ("Bloomelle uses Petal Dance!")
    
    def heal(self) -> str:
        return ("Bloomelle heals itself and others for a large amount")


class HealingCreatureFactory(CreatureFactory):
    def create_base(self) -> Creature:
        return Sproutling("Sproutling", "Grass")


    def create_evolved(self) -> Creature:
        return Bloomelle("Bloomelle", "Grass/Fairy")


class Shiftling(Creature, TransformCapability):
    def __init__(self, name: str, c_type: str) -> None:
        super().__init__(name, c_type)
        self.transformed = False


    def attack(self) -> str:
        if self.transformed:
            return ("Shiftling performs a boosted strike!")
        return ("Shiftling attacks normally.")


    def transform(self) -> str:
        self.transformed = True
        return ("Shiftling shifts into a sharper form!")


    def revert(self) -> str:
        return ("Shiftling returns to normal.")



class Morphagon(Creature, TransformCapability):
    def __init__(self, name = str, c_type = str):
        super().__init__(name, c_type)
        self.transformed = False


    def attack(self) -> str:
        if self.transformed:
            return ("Morphagon unleashes a devastating morph strike!")
        return ("Morphagon attacks normally.")


    def transform(self) -> str:
        self.transformed = True
        return ("Morphagon morphs into a dragonic battle form!")


    def revert(self) -> str:
        return ("Morphagon stabilizes its form.")



class TransformCreatureFactory(CreatureFactory):
    def create_base(self) -> Creature:
        return Shiftling("Shiftling", "Normal")


    def create_evolved(self) -> Creature:
        return Morphagon("Morphagon", "Normal/Dragon")