#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <stdexcept>
#include <vector>

class Direction{
public:
    enum class Dir
    {
        LEFT  = 0,
        DOWN = 1,
        RIGHT = 2,
        UP   = 3,
        NONE = 4
    };
    static const Dir LEFT = Dir::LEFT;
    static const Dir DOWN = Dir::DOWN;
    static const Dir RIGHT = Dir::RIGHT;
    static const Dir UP = Dir::UP;
    static const Dir NONE = Dir::NONE;
    static std::vector<Dir> DIRECTIONS;
    static std::string directionToString(Dir direction);
    static Dir stringToDirection(std::string direction);
    static int dirToInt(Dir direction);
    static Dir intToDir(int direction);
    static sf::Vector2i dirToVector(Dir direction);
};