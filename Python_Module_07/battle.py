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

fflame = FlameFactory().create_base()
aaqua = AquaFactory().create_base()

print(fflame.describe())
print("vs.")
print(aaqua.describe())
print("fight!")
print(fflame.attack())
print(aaqua.attack())
