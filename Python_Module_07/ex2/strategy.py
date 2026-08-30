from abc import ABC, abstractmethod
from ex0.creature import Creature
from ex1.capability import Shiftling, Morphagon, Sproutling, Bloomelle

class BattleStrategy(ABC):
    @abstractmethod
    def act(self, creature: Creature) -> None:
        pass


    @abstractmethod
    def is_valid(self, creature: Creature) -> bool:
        pass

class NormalStrategy(BattleStrategy):
    def act(self, creature: Creature) -> None:
        if not self.is_valid(creature):
            raise TypeError(
                f"Invalid Creature '{creature._name}' for normal strategy"
            )
        print(creature.attack())


    def is_valid(self, creature: Creature) -> bool:
        return True
    

class AggressiveStrategy(BattleStrategy):
    def act(self, creature: Creature) -> None:
        if not self.is_valid(creature):
            raise TypeError(
                f"Invalid Creature '{creature._name}' for Aggressive strategy"
            )
        print(creature.transform())
        print(creature.attack())
        print(creature.revert())


    def is_valid(self, creature: Creature) -> bool:
        return isinstance(creature, (Shiftling, Morphagon))


class DefensiveStrategy(BattleStrategy):
    def act(self, creature: Creature) -> None:
        if not self.is_valid(creature):
            raise TypeError(
                f"Invalid Creature '{creature._name}' for Defensive strategy"
            )
        
        print(creature.attack())
        print(creature.heal())


    def is_valid(self, creature: Creature) -> bool:
        return isinstance(creature, (Sproutling, Bloomelle))

