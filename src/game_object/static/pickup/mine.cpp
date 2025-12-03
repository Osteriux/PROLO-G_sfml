#include "mine.hpp"

Mine::Mine(int x, int y)
    : Pickup(std::make_unique<MultiTexture>(Pickup::texturePath(Pickup::MINE), 2), x, y)
{
    type = PickupType::MINE;
    active = false;
}

std::string Mine::getDescription() const
{
    return "Mine";
}

void Mine::action(DynamicGameObject *user)
{
    std::cout << "Mine action" << std::endl;
}
