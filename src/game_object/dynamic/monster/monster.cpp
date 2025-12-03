#include "monster.hpp"
#include "../../../manager/game_manager.hpp"

Monster::Monster(std::string type, int health, int speed, int x, int y)
    : DynamicGameObject(health, speed, std::make_unique<MultiTexture>("assets/dynamic/" + type + ".png", 1), x, y)
{
}

float Monster::heuristic(std::pair<int, int> a, std::pair<int, int> b)
{
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

Direction::Dir Monster::pathFinding(int playerX, int playerY)
{
    int monsterX = currCase->getX();
    int monsterY = currCase->getY();
    std::map<std::pair<int, int>, std::map<Direction::Dir, bool>> adjacents = GameManager::getInstance().getMap()->getAdjacents();
    std::map<std::pair<int, int>, std::pair<int, int>> parents;
    std::map<std::pair<int, int>, float> gScore;
    std::map<std::pair<int, int>, float> fScore;
    std::priority_queue<std::pair<float, std::pair<int, int>>, std::vector<std::pair<float, std::pair<int, int>>>, std::greater<>> openSet;

    std::pair<int, int> monster = std::make_pair(monsterX, monsterY);
    std::pair<int, int> player = std::make_pair(playerX, playerY);

    gScore[monster] = 0;
    fScore[monster] = heuristic(monster, player);
    openSet.push(std::make_pair(fScore[monster], monster));
    parents[monster] = std::make_pair(-1, -1);

    while (!openSet.empty())
    {
        std::pair<int, int> current = openSet.top().second;
        openSet.pop();

        if (current == player)
        {
            break;
        }

        for (auto direction : Direction::DIRECTIONS)
        {
            auto next = std::make_pair(current.first + Direction::dirToVector(direction).x, current.second + Direction::dirToVector(direction).y);
            if (adjacents[current][direction])
            {
                float tentative_gScore = gScore[current] + 1; // Assuming uniform cost for each move
                if (gScore.find(next) == gScore.end() || tentative_gScore < gScore[next])
                {
                    parents[next] = current;
                    gScore[next] = tentative_gScore;
                    fScore[next] = gScore[next] + heuristic(next, player);
                    openSet.push(std::make_pair(fScore[next], next));
                }
            }
        }
    }

    std::pair<int, int> current = player;
    while (parents.find(current) != parents.end() && parents[current] != monster)
    {
        current = parents[current];
    }

    if (current.first == monster.first - 1)
    {
        return Direction::Dir::LEFT;
    }
    if (current.first == monster.first + 1)
    {
        return Direction::Dir::RIGHT;
    }
    if (current.second == monster.second - 1)
    {
        return Direction::Dir::UP;
    }
    if (current.second == monster.second + 1)
    {
        return Direction::Dir::DOWN;
    }
    return Direction::Dir::NONE;
}

std::string Monster::monsterTypeToString(MonsterType type)
{
    switch (type)
    {
    case DOG:
        return "dog";
    case HOWLER:
        return "howler";
    case CRAWLER:
        return "crawler";
    default:
        return "dog";
    }
}

Monster::MonsterType Monster::monsterTypeFromString(std::string type)
{
    if (type == "dog")
        return DOG;
    if (type == "howler")
        return HOWLER;
    if (type == "crawler")
        return CRAWLER;
    return DOG;
}

int Monster::monsterTypeToInt(MonsterType type)
{
    return static_cast<int>(type);
}

Monster::MonsterType Monster::intToMonsterType(int type)
{
    return static_cast<MonsterType>(type);
}