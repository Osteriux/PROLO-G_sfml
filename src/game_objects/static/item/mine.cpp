#include "mine.h"

Mine::Mine(int x, int y, GameManager* gameManager)
    : Item("assets/static/MINE.png", gameManager, x, y)
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
