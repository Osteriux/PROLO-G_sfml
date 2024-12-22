#pragma once
#include <queue>
#include <map>
#include <cmath>
#include <functional>
#include "../dynamic_game_object.h"
#include "../../../manager/game_manager.h"

class Monstre : public DynamicGameObject
{
protected:
    float heuristic(std::pair<int, int> a, std::pair<int, int> b);
    Direction::Dir pathFinding(int joueurX, int joueurY);
public:
    enum MonstreType
    {
        CHIEN,
        HURLEUR,
        RAMPANT
    };
    static std::string monstreTypeToString(MonstreType type);
    static MonstreType monstreTypeFromString(std::string type);
    static int monstreTypeToInt(MonstreType type);
    static MonstreType intToMonstreType(int type);

    Monstre(sf::Vector2f position, GameManager* gameManager, std::string type, int health, float speed);
    ~Monstre() = default;
};