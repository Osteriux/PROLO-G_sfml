#include "multi_texture.h"

MultiTexture::MultiTexture(std::string texture_path, int lineCount, int columnCount, std::vector<int> columnsSize)
    : lineCount(lineCount), columnCount(columnCount), columnsSize(columnsSize)
{
    if (!texture.loadFromFile(texture_path))
    {
        std::cerr << "Error loading texture : " << texture_path << std::endl;
    }
    currLine = 0;
    currColumn = 0;
    setTexture(texture);
    rect = sf::IntRect(0, 0, texture.getSize().x / columnCount, texture.getSize().y / lineCount);
    setTextureRect(rect);
}

MultiTexture::MultiTexture(std::string texturePath, int nbImages)
    : lineCount(1), columnCount(nbImages), columnsSize(1, nbImages)
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

MultiTexture::MultiTexture(sf::Color color, int width, int height, sf::Vector2f offset)
    : lineCount(1), columnCount(1), columnsSize(1, 1)
{
    // Create a render texture
    sf::RenderTexture renderTexture;
    renderTexture.create(32, 32);

    // Create a rectangle shape with the given specifications
    sf::RectangleShape shape(sf::Vector2f(width, height));
    shape.setPosition(offset);
    shape.setFillColor(color);

    // Render the rectangle shape to the render texture
    renderTexture.clear(sf::Color::Transparent);
    renderTexture.draw(shape);
    renderTexture.display();

    // Get the texture from the render texture
    texture = renderTexture.getTexture();

    // Initialize other member variables
    currLine = 0;
    currColumn = 0;
    rect = sf::IntRect(0, 0, 32, 32);
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
