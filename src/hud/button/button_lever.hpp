#pragma once
#include "button_base.hpp"

class ButtonLever : public ButtonBase
{
private:
    sf::RectangleShape outline;

public:
    ButtonLever(sf::Vector2f position, sf::Vector2f size, sf::Color backgroundColor = sf::Color::White, sf::Color outlineColor = sf::Color::White);
    bool isClicked(sf::Vector2f mousePosition) override;
    void draw(sf::RenderWindow &window) override;
    ~ButtonLever() = default;
};