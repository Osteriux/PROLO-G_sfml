#include "matrix_animation.h"

MatrixAnimation::MatrixAnimation(std::string texture_path, int nbLines, int nbColumns, int* columnsSize, float switchTime)
    : MultiTexture(texture_path, nbLines, nbColumns, columnsSize), switchTime(switchTime)
{
    if (!texture.loadFromFile(texture_path))
    {
        std::cerr << "Error loading texture : " << texture_path << std::endl;
    }
    currLine = 0;
    currColumn = 0;
    currentTime = 0;
    rect = sf::IntRect(0, 0, texture.getSize().x / nbColumns, texture.getSize().y / nbLines);
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