#include "bomb.hpp"
#include "../../dynamic/player/player.hpp"
#include "../../../utils/logger/logger.hpp"

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
    Logger::log("Bomb action", Logger::INFO);
}
