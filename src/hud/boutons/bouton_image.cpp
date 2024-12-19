#include "bouton_image.h"

ButtonImage::ButtonImage(sf::Vector2f position, sf::Vector2f size, std::string texturePath, sf::Color backgroundColor)
    : ButtonBase(position, size, backgroundColor)
{
    if (!texture.loadFromFile(texturePath))
    {
        std::cerr << "Error loading texture : " << texturePath << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
}

void ButtonImage::draw(sf::RenderWindow &window)
{
    ButtonBase::draw(window);
    window.draw(sprite);
}