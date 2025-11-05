#include "monstre.h"
#include "../../../manager/game_manager.h"

Monstre::Monstre(GameManager *gameManager, std::string type, int health, int speed, int x, int y)
    : DynamicGameObject(health, speed, std::make_unique<MultiTexture>("assets/dynamic/" + type + ".png", 1), gameManager, x, y)
{
}

float Monstre::heuristic(std::pair<int, int> a, std::pair<int, int> b)
{
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

Direction::Dir Monstre::pathFinding(int joueurX, int joueurY)
{
    int monsterX = currCase->getX();
    int monsterY = currCase->getY();
    std::map<std::pair<int, int>, std::map<Direction::Dir, bool>> adjacents = gameManager->getCarte()->getAdjacents();
    std::map<std::pair<int, int>, std::pair<int, int>> parents;
    std::map<std::pair<int, int>, float> gScore;
    std::map<std::pair<int, int>, float> fScore;
    std::priority_queue<std::pair<float, std::pair<int, int>>, std::vector<std::pair<float, std::pair<int, int>>>, std::greater<>> openSet;

    std::pair<int, int> monster = std::make_pair(monsterX, monsterY);
    std::pair<int, int> player = std::make_pair(joueurX, joueurY);

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

std::string Monstre::monstreTypeToString(MonstreType type)
{
    switch (type)
    {
    case CHIEN:
        return "chien";
    case HURLEUR:
        return "hurleur";
    case RAMPANT:
        return "rampant";
    default:
        return "chien";
    }
}

Monstre::MonstreType Monstre::monstreTypeFromString(std::string type)
{
    if (type == "chien")
        return CHIEN;
    if (type == "hurleur")
        return HURLEUR;
    if (type == "rampant")
        return RAMPANT;
    return CHIEN;
}

int Monstre::monstreTypeToInt(MonstreType type)
{
    return static_cast<int>(type);
}

Monstre::MonstreType Monstre::intToMonstreType(int type)
{
    return static_cast<MonstreType>(type);
}