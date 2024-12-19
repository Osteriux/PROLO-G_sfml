#include "dynamic_game_object.h"

DynamicGameObject::DynamicGameObject(int health, int speed ,std::unique_ptr<MultiTexture> animation, Carte* carte, int x, int y)
    : GameObject(std::move(animation), carte, x, y), health(health), speed(speed)
{
}

int DynamicGameObject::getHealth()
{
    return health;
}

void DynamicGameObject::move(Direction::Dir direction)
{
    int x = currCase->getX();
    int y = currCase->getY();
    Case* nextCase = nullptr;
    switch (direction)
    {
    case Direction::UP:
        nextCase = carte->getCase(x-1, y);
        break;
    case Direction::DOWN:
        nextCase = carte->getCase(x+1, y);
        break;
    case Direction::LEFT:
        nextCase = carte->getCase(x, y-1);
        break;
    case Direction::RIGHT:
        nextCase = carte->getCase(x, y+1);
        break;
    default:
        break;
    }
    if (nextCase)
    {
        currCase->transferEntity(nextCase);
        currCase = nextCase;
    }else{
        std::cerr << "Error moving " << Direction::directionToString(direction) << " from : (" << x << "," << y << ")" << std::endl;
    }
}