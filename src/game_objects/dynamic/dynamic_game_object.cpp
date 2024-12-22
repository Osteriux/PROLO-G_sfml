#include "../../manager/game_manager.h"
#include "../../carte/carte.h"
#include "../../carte/case.h"
#include "dynamic_game_object.h"

DynamicGameObject::DynamicGameObject(int health, int speed ,std::unique_ptr<MultiTexture> animation, GameManager* , int x, int y)
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
        std::cerr << "Error: " << Direction::directionToString(direction) << " is not a valid move" << std::endl;
        return;
    }
    std::cout << "1" << std::endl;
    int x = currCase->getX();
    std::cout << "2" << std::endl;
    int y = currCase->getY();
    std::cout << "3" << std::endl;
    Case* nextCase = currCase;
    std::cout << "4" << std::endl;
    Carte* carte = gameManager->getCarte();
    std::cout << "5" << std::endl;
    switch (direction)
    {
    case Direction::UP:
        std::cout << "6" << std::endl;
        nextCase = carte->getCase(x-1, y);
        std::cout << "7" << std::endl;
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
    std::cout << "Moving " << Direction::directionToString(direction) << " from : (" << x << "," << y << ") to (" << nextCase->getX() << "," << nextCase->getY() << ")" << std::endl;
    if (nextCase)
    {
        currCase->transferEntity(nextCase);
        currCase = nextCase;
    }else{
        std::cerr << "Error moving " << Direction::directionToString(direction) << " from : (" << x << "," << y << ")" << std::endl;
    }
}