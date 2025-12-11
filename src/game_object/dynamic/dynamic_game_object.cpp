#include "../../manager/game_manager.hpp"
#include "../../map/map.hpp"
#include "../../map/case.hpp"
#include "dynamic_game_object.hpp"
#include "../../utils/logger/logger.hpp"

DynamicGameObject::DynamicGameObject(int health, int speed, std::unique_ptr<MultiTexture> animation, int x, int y)
    : GameObject(std::move(animation), x, y), health(health), speed(speed)
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
        Logger::log(Direction::directionToString(direction) + " is not a valid move", Logger::WARNING);
        return;
    }
    int x = currCase->getX();
    int y = currCase->getY();
    Case *nextCase = currCase;
    Map *map = GameManager::getInstance().getMap();
    switch (direction)
    {
    case Direction::UP:
        nextCase = map->getCase(x - 1, y);
        break;
    case Direction::DOWN:
        nextCase = map->getCase(x + 1, y);
        break;
    case Direction::LEFT:
        nextCase = map->getCase(x, y - 1);
        break;
    case Direction::RIGHT:
        nextCase = map->getCase(x, y + 1);
        break;
    default:
        break;
    }
    if (nextCase)
    {
        currCase->transferEntity(nextCase);
        currCase = nextCase;
    }
    else
    {
        Logger::log("Error moving " + Direction::directionToString(direction) + " from : (" + std::to_string(x) + "," + std::to_string(y) + ")", Logger::ERROR);
    }
}