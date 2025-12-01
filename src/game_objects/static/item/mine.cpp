#include "mine.h"

Mine::Mine(int x, int y)
    : Item(std::make_unique<MultiTexture>(Item::texturePath(Item::MINE), 2), x, y)
{
    type = ItemType::MINE;
    active = false;
}

std::string Mine::getDescription() const
{
    return "Mine";
}

void Mine::action(DynamicGameObject* user)
{
    std::cout << "Mine action" << std::endl;
}
