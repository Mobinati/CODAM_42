from ex1 import HealingCreatureFactory, TransformCreatureFactory


print("Testing Creature with healing capability")
factory1 = HealingCreatureFactory()

creature1 = factory1.create_base()
print("base:")
print(creature1.describe())
print(creature1.attack())
print(creature1.heal())

creature2 = factory1.create_evolved()
print("evolved:")
print(creature2.describe())
print(creature2.attack())
print(creature2.heal())

print('\n')
print("Testing Creature with transform capability")
factory2 = TransformCreatureFactory()

creature1 = factory2.create_base()
print("base:")
print(creature1.describe())
print(creature1.attack())
print(creature1.transform())
print(creature1.describe())
print(creature1.attack())
print(creature1.revert())

creature2 = factory2.create_evolved()
print("evolved:")
print(creature2.describe())
print(creature2.attack())
print(creature2.transform())
print(creature2.describe())
print(creature2.attack())
print(creature2.revert())
