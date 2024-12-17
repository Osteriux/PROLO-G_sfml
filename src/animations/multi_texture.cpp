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

MultiTexture::MultiTexture(){
    MultiTexture(sf::Color::Yellow, 1, 1);
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
