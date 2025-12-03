#include "../../../manager/game_manager.hpp"
#include "player.hpp"

Player::Player(int x, int y, int health)
    : DynamicGameObject(health, 1, std::make_unique<MultiTexture>("assets/dynamic/PLAYER.png", 1), x, y), inventory()
{
}

Inventory& Player::getInventory()
{
    return inventory;
}

std::string Player::getDescription() const
{
    return "Player";
}

void Player::move(Direction::Dir direction)
{
    DynamicGameObject::move(direction);
}