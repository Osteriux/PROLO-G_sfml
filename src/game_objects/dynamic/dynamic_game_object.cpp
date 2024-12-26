#include "../../manager/game_manager.h"
#include "../../carte/carte.h"
#include "../../carte/case.h"
#include "dynamic_game_object.h"

DynamicGameObject::DynamicGameObject(int health, int speed ,std::unique_ptr<MultiTexture> animation, GameManager* gameManager, int x, int y)
    : GameObject(std::move(animation), gameManager, x, y), health(health), speed(speed)
{
}

int DynamicGameObject::getHealth()
{
    return health;
}

void DynamicGameObject::move(Direction::Dir direction)
{
    std::map<Direction::Dir, bool> adj = currCase->getAdjacent();
    if (!adj[direction])
    {
        std::cout << Direction::directionToString(direction) << " is not a valid move" << std::endl;
        return;
    }
    int x = currCase->getX();
    int y = currCase->getY();
    Case* nextCase = currCase;
    Carte* carte = gameManager->getCarte();
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