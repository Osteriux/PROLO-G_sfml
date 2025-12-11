#include "button_lever.hpp"
#include "../../utils/logger/logger.hpp"

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
    Logger::log("ButtonLever isClicked: " + std::string(clicked ? "true" : "false"), Logger::INFO);
    Logger::log("Background position: (" + std::to_string(background.getPosition().x) + ", " + std::to_string(background.getPosition().y) + ")", Logger::DEBUG);
    return clicked;
}

void ButtonLever::draw(sf::RenderWindow &window)
{
    ButtonBase::draw(window);
    window.draw(outline);
}

void ButtonLever::setPosition(sf::Vector2f newPosition)
{
    ButtonBase::setPosition(newPosition);
    outline.setPosition(newPosition);
}