#include "mine.h"

Mine::Mine(int x, int y, GameManager* gameManager)
    : Item(std::make_unique<MultiTexture>(Item::texturePath(Item::MINE), 2), gameManager, x, y)
{
    type = ItemType::MINE;
    active = false;
}

std::string Mine::getDescription()
{
    return "Mine";
}

void Mine::action(DynamicGameObject* user)
{
    std::cout << "Mine action" << std::endl;
}
