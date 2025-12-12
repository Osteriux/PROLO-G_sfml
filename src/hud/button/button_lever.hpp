#pragma once
#include "button_base.hpp"

class Lever; // Forward declaration

class ButtonLever : public ButtonBase
{
private:
    sf::RectangleShape outline;
    Lever* lever; // Reference to actual lever object

public:
    ButtonLever(sf::Vector2f position, sf::Vector2f size, Lever* leverPtr);
    bool isClicked(sf::Vector2f mousePosition) override;
    void draw(sf::RenderWindow &window) override;
    void setPosition(sf::Vector2f newPosition);
    Lever* getLever() const;
    ~ButtonLever() = default;
};