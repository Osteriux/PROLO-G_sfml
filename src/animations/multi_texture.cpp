#include "multi_texture.h"

MultiTexture::MultiTexture(std::string texture_path, int nbLines, int nbColumns, std::vector<int> columnsSize)
    : nbLines(nbLines), nbColumns(nbColumns), columnsSize(columnsSize)
{
    if (!texture.loadFromFile(texture_path))
    {
        std::cerr << "Error loading texture : " << texture_path << std::endl;
    }
    currLine = 0;
    currColumn = 0;
    setTexture(texture);
    rect = sf::IntRect(0, 0, texture.getSize().x / nbColumns, texture.getSize().y / nbLines);
    setTextureRect(rect);
}

MultiTexture::MultiTexture(std::string texturePath, int nbImages)
    : nbLines(1), nbColumns(nbImages), columnsSize(1, nbImages)
{
    if (!texture.loadFromFile(texturePath))
    {
        std::cerr << "Error loading texture : " << texturePath << std::endl;
    }
    currLine = 0;
    currColumn = 0;
    rect = sf::IntRect(0, 0, texture.getSize().x / nbImages, texture.getSize().y);
    setTexture(texture);
    setTextureRect(rect);
}

sf::Vector2f MultiTexture::getSize() const{
    return sf::Vector2f(rect.width, rect.height);
}

void MultiTexture::setLine(int line){
    currLine = line;
    rect.top = currLine * rect.height;
    setTextureRect(rect);
}

void MultiTexture::setColumn(int column){
    currColumn = column;
    rect.left = currColumn * rect.width;
    setTextureRect(rect);
}

bool MultiTexture::update(float dt){
    return false;
}
