from abc import ABC, abstractmethod



class Creature(ABC):
	def __init__(self, name, c_type) -> None:
		self._name = name
		self._type = c_type


	@abstractmethod
	def attack(self) -> str:
		pass


	def describe(self):
		return (f"{self._name} is a {self._type} type creature")


class Flameling(Creature):
	def attack(self) -> str:
		return ("Flameling uses Ember!")


class Pyrodon(Creature):
	def attack(self) -> str:
		return ("Pyrodon uses Flamethrower!")


class Aquabub(Creature):
	def attack(self) -> str:
		return ("Aquabub uses Water Gun!")


class Torragon(Creature):
	def attack(self) -> str:
		return ("Torragon uses Hydro Pump!")
