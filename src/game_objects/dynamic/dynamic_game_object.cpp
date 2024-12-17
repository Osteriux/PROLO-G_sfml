#include "dynamic_game_object.h"

DynamicGameObject::DynamicGameObject(int health, int speed ,std::unique_ptr<MultiTexture> animation, Carte* carte, int x, int y)
    : GameObject(std::move(animation), carte, x, y), health(health), speed(speed)
{
}

void DynamicGameObject::move(Direction::Dir direction)
{
    int x = currCase->getX();
    int y = currCase->getY();
    Case* nextCase = nullptr;
    switch (direction)
    {
    case Direction::UP:
        nextCase = carte->getCase(x, y - 1);
        break;
    case Direction::DOWN:
        nextCase = carte->getCase(x, y + 1);
        break;
    case Direction::LEFT:
        nextCase = carte->getCase(x - 1, y);
        break;
    case Direction::RIGHT:
        nextCase = carte->getCase(x + 1, y);
        break;
    default:
        break;
    }
    if (nextCase)
    {
        currCase->transferEntity(nextCase);
        currCase = nextCase;
    }else{
        std::cerr << "Error moving entity to : (" << x << "," << y << ")" << std::endl;
    }
}