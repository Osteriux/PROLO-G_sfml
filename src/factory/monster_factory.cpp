#include "monster_factory.hpp"
#include "../game_object/dynamic/monster/dog.hpp"
#include "../utils/logger/logger.hpp"

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
        Logger::log("Invalid monster type: " + std::to_string(static_cast<int>(type)), Logger::ERROR);
        throw std::invalid_argument("Invalid monster type");
    }
}