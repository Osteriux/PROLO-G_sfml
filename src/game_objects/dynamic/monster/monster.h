#pragma once
#include <queue>
#include <map>
#include <cmath>
#include <functional>
#include "../dynamic_game_object.h"

// Forward declaration to avoid circular dependency with GameManager -> Map -> MonsterFactory -> Monster
class GameManager;

class Monster : public DynamicGameObject
{
protected:
    float heuristic(std::pair<int, int> a, std::pair<int, int> b);
    Direction::Dir pathFinding(int playerX, int playerY);

public:
    enum MonsterType
    {
        DOG,
        HOWLER,
        CRAWLER
    };
    static std::string monsterTypeToString(MonsterType type);
    static MonsterType monsterTypeFromString(std::string type);
    static int monsterTypeToInt(MonsterType type);
    static MonsterType intToMonsterType(int type);

    Monster(std::string type, int health, int speed, int x, int y);
    ~Monster() = default;
};