#include "monster_factory.h"
#include "../game_objects/dynamic/monster/dog.h"

std::unique_ptr<Monster> MonsterFactory::createMonster(Monster::MonsterType type, int x, int y)
{
    switch (type)
    {
    case Monster::DOG:
        return std::make_unique<Dog>(x, y);
    case Monster::HOWLER:
        // return std::make_unique<Howler>(gameManager, x, y);
    case Monster::CRAWLER:
        // return std::make_unique<Crawler>(gameManager, x, y);
    default:
        throw std::invalid_argument("Invalid monster type");
    }
}