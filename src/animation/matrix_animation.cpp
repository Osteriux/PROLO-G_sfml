#include "matrix_animation.hpp"
#include "../utils/logger/logger.hpp"

MatrixAnimation::MatrixAnimation(std::string texture_path, int lineCount, int columnCount, std::vector<int> columnsSize, float switchTime)
    : MultiTexture(texture_path, lineCount, columnCount, columnsSize), switchTime(switchTime)
{
    if (!texture.loadFromFile(texture_path))
    {
        Logger::log("Error loading texture : " + texture_path, Logger::ERROR);
    }
    currLine = 0;
    currColumn = 0;
    currentTime = 0;
    rect = sf::IntRect(0, 0, texture.getSize().x / columnCount, texture.getSize().y / lineCount);
    setTextureRect(rect);
}

void MatrixAnimation::setLine(int line)
{
    currLine = line;
    rect.top = currLine * rect.height;
    rect.left = 0;
    setTextureRect(rect);
}

bool MatrixAnimation::update(float dt)
{
    bool warped = false;
    currentTime += dt;
    if (currentTime >= switchTime)
    {
        currentTime = 0;
        currColumn++;
        if (currColumn >= columnsSize[currLine])
        {
            currColumn = 0;
            warped = true;
        }
        rect.left = currColumn * rect.width;
        setTextureRect(rect);
    }
    return warped;
}