#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class MultiTexture : public sf::Sprite
{
protected:
    sf::Texture texture;
    int nbColumns, nbLines;
    int currLine, currColumn;
    std::vector<int> columnsSize;
    sf::IntRect rect;
public:
    MultiTexture(std::string texture_path, int nbLines, int nbColumns, std::vector<int> columnsSize);
    MultiTexture(std::string texturePath, int nbImages);
    sf::Vector2f getSize() const;
    virtual void setLine(int line);
    virtual void setColumn(int column);
    virtual bool update(float dt);
    ~MultiTexture() = default;
};
