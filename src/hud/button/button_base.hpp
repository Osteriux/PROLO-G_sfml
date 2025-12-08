#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class ButtonBase
{
protected:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::RectangleShape background;

public:
    ButtonBase(sf::Vector2f position, sf::Vector2f size, sf::Color backgroundColor = sf::Color::White);
    virtual bool isClicked(sf::Vector2f mousePosition);
    virtual void draw(sf::RenderWindow &window);
    void setPosition(sf::Vector2f newPosition);
    sf::Vector2f getPosition() const;
    ~ButtonBase() = default;
};