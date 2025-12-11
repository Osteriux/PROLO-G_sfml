#include "button_image.hpp"
#include "../../utils/logger/logger.hpp"

ButtonImage::ButtonImage(sf::Vector2f position, sf::Vector2f size, std::string texturePath, sf::Color backgroundColor)
    : ButtonBase(position, size, backgroundColor)
{
    if (!texture.loadFromFile(texturePath))
    {
        Logger::log("Error loading texture : " + texturePath, Logger::ERROR);
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

void ButtonImage::setPosition(sf::Vector2f newPosition)
{
    ButtonBase::setPosition(newPosition);
    sprite.setPosition(newPosition);
}