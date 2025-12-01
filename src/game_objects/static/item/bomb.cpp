#include "bomb.h"
#include "../../dynamic/player/player.h"

Bomb::Bomb(int x, int y)
    : Item(std::make_unique<MultiTexture>(Item::texturePath(Item::BOMB), 2), x, y)
{
    type = ItemType::BOMB;
}

std::string Bomb::getDescription() const
{
    return "Bomb";
}

void Bomb::action(DynamicGameObject* user)
{
    std::cout << "Bomb action" << std::endl;
}
