#include "button_base.hpp"

ButtonBase::ButtonBase(sf::Vector2f position, sf::Vector2f size, sf::Color backgroundColor)
    : position(position), size(size)
{
    background.setFillColor(backgroundColor);
    background.setPosition(position);
    background.setSize(size);
}

bool ButtonBase::isClicked(sf::Vector2f mousePosition)
{
    return background.getGlobalBounds().contains(mousePosition);
}

void ButtonBase::draw(sf::RenderWindow &window)
{
    window.draw(background);
}

void ButtonBase::setPosition(sf::Vector2f newPosition)
{
    position = newPosition;
    background.setPosition(newPosition);
}

sf::Vector2f ButtonBase::getPosition() const
{
    return position;
}