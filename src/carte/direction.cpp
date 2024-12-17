#include "direction.h"

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
    default:
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
    else
    {
        throw std::invalid_argument("Invalid direction");
    }
}

int Direction::dirToInt(Dir direction)
{
    switch (direction)
    {
    case Dir::LEFT:
        return 0;
    case Dir::DOWN:
        return 1;
    case Dir::RIGHT:
        return 2;
    case Dir::UP:
        return 3;
    default:
        throw std::invalid_argument("Invalid direction");
    }
}

Direction::Dir Direction::intToDir(int direction)
{
    switch (direction)
    {
    case 0:
        return Dir::LEFT;
    case 1:
        return Dir::DOWN;
    case 2:
        return Dir::RIGHT;
    case 3:
        return Dir::UP;
    default:
        throw std::invalid_argument("Invalid direction");
    }
}
