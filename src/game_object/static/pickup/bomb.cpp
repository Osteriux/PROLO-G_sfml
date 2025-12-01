#include "bomb.h"
#include "../../dynamic/player/player.h"

Bomb::Bomb(int x, int y)
    : Pickup(std::make_unique<MultiTexture>(Pickup::texturePath(Pickup::BOMB), 2), x, y)
{
    type = PickupType::BOMB;
}

std::string Bomb::getDescription() const
{
    return "Bomb";
}

void Bomb::action(DynamicGameObject *user)
{
    std::cout << "Bomb action" << std::endl;
}
