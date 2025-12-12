#include "button_lever.hpp"
#include "../../game_object/static/interactible/lever.hpp"
#include "../../utils/logger/logger.hpp"

ButtonLever::ButtonLever(sf::Vector2f position, sf::Vector2f size, Lever* leverPtr)
    : ButtonBase(position, size, leverPtr->getColor()), lever(leverPtr)
{
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(leverPtr->getColor());
    outline.setOutlineThickness(2);
    outline.setPosition(position);
    outline.setSize(size);

    background.setSize(sf::Vector2f(size.x, size.y / 2));
    // Position background based on actual lever state
    if (leverPtr->isActivated())
    {
        background.setPosition(position.x, position.y + size.y / 2);
    }
    else
    {
        background.setPosition(position);
    }
}

bool ButtonLever::isClicked(sf::Vector2f mousePosition)
{
    bool clicked = ButtonBase::isClicked(mousePosition);
    
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
    
    // Update background position based on lever state
    if (lever->isActivated())
    {
        background.setPosition(newPosition.x, newPosition.y + size.y / 2);
    }
    else
    {
        background.setPosition(newPosition);
    }
}

Lever* ButtonLever::getLever() const
{
    return lever;
}