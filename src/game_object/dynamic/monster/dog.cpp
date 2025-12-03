#include "dog.hpp"

Dog::Dog(int x, int y)
    : Monster(Monster::monsterTypeToString(Monster::DOG), 100, 2, x, y)
{
}

std::string Dog::getDescription() const
{
    return "Dog";
}