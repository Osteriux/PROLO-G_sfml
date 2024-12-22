#include "lever.h"

Lever::Lever(std::unique_ptr<MultiTexture> animation, GameManager* gameManager, int x, int y, int doorId)
    : StaticGameObject(std::move(animation), gameManager, x, y), activated(false), doorId(doorId)
{
}

void Lever::action(DynamicGameObject* user)
{
    activated = !activated;
    if (activated)
    {
        std::cout << "Door " << doorId << " opened" << std::endl;
    }
    else
    {
        std::cout << "Door " << doorId << " closed" << std::endl;
    }
}