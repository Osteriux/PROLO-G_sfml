#include "direction.hpp"
#include "../utils/logger/logger.hpp"

std::string Direction::directionToString(Dir direction)
{
    switch (direction)
    {
    case Dir::LEFT:
        return "LEFT";
    case Dir::DOWN:
        return "DOWN";
    case Dir::RIGHT:
        return "RIGHT";
    case Dir::UP:
        return "UP";
    case Dir::NONE:
        return "NONE";
    default:
        Logger::log("Invalid direction", Logger::ERROR);
        throw std::invalid_argument("Invalid direction");
    }
}

Direction::Dir Direction::stringToDirection(std::string direction)
{
    if (direction == "LEFT")
    {
        return Dir::LEFT;
    }
    else if (direction == "DOWN")
    {
        return Dir::DOWN;
    }
    else if (direction == "RIGHT")
    {
        return Dir::RIGHT;
    }
    else if (direction == "UP")
    {
        return Dir::UP;
    }
    else if (direction == "NONE")
    {
        return Dir::NONE;
    }
    else
    {
        Logger::log("Invalid direction: " + direction, Logger::ERROR);
        throw std::invalid_argument("Invalid direction");
    }
}

int Direction::dirToInt(Dir direction)
{
    return static_cast<int>(direction);
}

Direction::Dir Direction::intToDir(int direction)
{
    return static_cast<Dir>(direction);
}

sf::Vector2i Direction::dirToVector(Dir direction)
{
    switch (direction)
    {
    case Dir::LEFT:
        return sf::Vector2i(-1, 0);
    case Dir::DOWN:
        return sf::Vector2i(0, 1);
    case Dir::RIGHT:
        return sf::Vector2i(1, 0);
    case Dir::UP:
        return sf::Vector2i(0, -1);
    case Dir::NONE:
        return sf::Vector2i(0, 0);
    default:
        Logger::log("Invalid direction", Logger::ERROR);
        throw std::invalid_argument("Invalid direction");
    }
}

std::vector<Direction::Dir> Direction::DIRECTIONS = {Dir::LEFT, Dir::DOWN, Dir::RIGHT, Dir::UP};
