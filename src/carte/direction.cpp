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