#include "bouton_levier.h"

ButtonLevier::ButtonLevier(sf::Vector2f position, sf::Vector2f size, sf::Color backgroundColor, sf::Color outlineColor)
    : ButtonBase(position, size, backgroundColor)
{
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(outlineColor);
    outline.setOutlineThickness(2);
    outline.setPosition(position);
    outline.setSize(size);

    background.setSize(sf::Vector2f(size.x , size.y / 2));
}

bool ButtonLevier::isClicked(sf::Vector2f mousePosition)
{
    bool clicked = ButtonBase::isClicked(mousePosition);
    if(clicked)
    {
        background.setPosition(position);
    }
    else
    {
        background.setPosition(position.x, position.y + size.y / 2);
    }
    return clicked;
}

void ButtonLevier::draw(sf::RenderWindow &window)
{
    ButtonBase::draw(window);
    window.draw(outline);
}