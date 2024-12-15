#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class MultiTexture : public sf::Sprite
{
protected:
    sf::Texture texture;
    int nbColumns, nbLines;
    int currLine, currColumn;
    int* columnsSize;
    sf::IntRect rect;
public:
    MultiTexture(std::string texture_path, int nbLines, int nbColumns, int* columnsSize);
    MultiTexture(std::string texturePath, int nbImages);
    MultiTexture(sf::Color color, int width, int height);
    void setLine(int line);
    virtual bool update(float dt);
    ~MultiTexture() = default;
};
