#include "lever.h"

Lever::Lever(std::unique_ptr<MultiTexture> animation, Carte* carte, int x, int y, int doorId)
    : StaticGameObject(std::move(animation), carte, x, y), activated(false), doorId(doorId)
{
}

void Lever::action(DynamicGameObject* user)
{
    activated = !activated;
    if (activated)
    {
        carte->addOpenedDoor(doorId);
        std::cout << "Door " << doorId << " opened" << std::endl;
    }
    else
    {
        carte->removeOpenedDoor(doorId);
        std::cout << "Door " << doorId << " closed" << std::endl;
    }
}