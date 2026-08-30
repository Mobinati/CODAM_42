from ex0 import FlameFactory, AquaFactory


print("Testing factory")

flame = FlameFactory()
creature = flame.create_base()
print(creature.describe())
print(creature.attack())

creature = flame.create_evolved()
print(creature.describe())
print(creature.attack())

print('\n')
print("Testing factory")

aqua = AquaFactory()
creature = aqua.create_base()
print(creature.describe())
print(creature.attack())

creature = aqua.create_evolved()
print(creature.describe())
print(creature.attack())

print('\n')
print("Testing battle")

flame = FlameFactory().create_base()
aqua = AquaFactory().create_base()

print(flame.describe())
print("vs.")
print(aqua.describe())
print("fight!")
print(flame.attack())
print(aqua.attack())