#pragma once
#include <memory>
#include "../game_object/dynamic/monster/monster.h"

class MonsterFactory
{
public:
    static std::unique_ptr<Monster> createMonster(Monster::MonsterType type, int x, int y);
};
