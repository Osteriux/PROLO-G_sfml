#include "button_lever.hpp"

ButtonLever::ButtonLever(sf::Vector2f position, sf::Vector2f size, sf::Color backgroundColor, sf::Color outlineColor)
    : ButtonBase(position, size, backgroundColor)
{
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(outlineColor);
    outline.setOutlineThickness(2);
    outline.setPosition(position);
    outline.setSize(size);

    background.setSize(sf::Vector2f(size.x, size.y / 2));
}

bool ButtonLever::isClicked(sf::Vector2f mousePosition)
{
    bool clicked = ButtonBase::isClicked(mousePosition);
    if (clicked)
    {
        background.setPosition(position.x, position.y + size.y / 2);
    }
    else
    {
        background.setPosition(position);
    }
    std::cout << "ButtonLever isClicked: " << clicked << std::endl;
    std::cout << "Background position: (" << background.getPosition().x << ", " << background.getPosition().y << ")" << std::endl;
    return clicked;
}

void ButtonLever::draw(sf::RenderWindow &window)
{
    ButtonBase::draw(window);
    window.draw(outline);
}