#include "multi_texture.h"

MultiTexture::MultiTexture(std::string texture_path, int nbLines, int nbColumns, std::vector<int>)
    : nbLines(nbLines), nbColumns(nbColumns), columnsSize(columnsSize)
{
    if (!texture.loadFromFile(texture_path))
    {
        std::cerr << "Error loading texture : " << texture_path << std::endl;
    }
    setTexture(texture);
    currLine = 0;
    currColumn = 0;
    rect = sf::IntRect(0, 0, texture.getSize().x / nbColumns, texture.getSize().y / nbLines);
}

MultiTexture::MultiTexture(std::string texturePath, int nbImages)
    : nbLines(nbImages), nbColumns(1)
{
    if (!texture.loadFromFile(texturePath))
    {
        std::cerr << "Error loading texture : " << texturePath << std::endl;
    }
    setTexture(texture);
    columnsSize = std::vector<int>(1, nbImages);
    currLine = 0;
    currColumn = 0;
    rect = sf::IntRect(0, 0, texture.getSize().x / nbImages, texture.getSize().y);
}

MultiTexture::MultiTexture(sf::Color color, int width, int height)
    : nbLines(1), nbColumns(1)
{
    sf::RectangleShape r(sf::Vector2f(width, height));
    r.setFillColor(color);
    sf::RenderTexture renderTexture;
    renderTexture.create(width, height);
    renderTexture.clear();
    renderTexture.draw(r);
    renderTexture.display();
    texture = renderTexture.getTexture();
    columnsSize = std::vector<int>(1, 1);
    currLine = 0;
    currColumn = 0;
    rect = sf::IntRect(0, 0, width, height);
    setTexture(texture);
}

void MultiTexture::setLine(int line){
    currLine = line;
    rect.top = currLine * rect.height;
    rect.left = 0;
    setTextureRect(rect);
}

bool MultiTexture::update(float dt){
    return false;
}
