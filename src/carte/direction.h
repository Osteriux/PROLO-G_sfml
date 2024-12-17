#pragma once
#include <string>
#include <stdexcept>

class Direction{
public:
    enum class Dir
    {
        LEFT  = 0,
        DOWN = 1,
        RIGHT = 2,
        UP   = 3,
    };
    static const Dir LEFT = Dir::LEFT;
    static const Dir DOWN = Dir::DOWN;
    static const Dir RIGHT = Dir::RIGHT;
    static const Dir UP = Dir::UP;
    static std::string directionToString(Dir direction);
    static Dir stringToDirection(std::string direction);
    static int dirToInt(Dir direction);
    static Dir intToDir(int direction);
};