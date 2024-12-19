#pragma once
#include "bouton_base.h"

class ButtonLevier : public ButtonBase {
private:
    sf::RectangleShape outline;
public:
    ButtonLevier(sf::Vector2f position, sf::Vector2f size, sf::Color backgroundColor = sf::Color::White, sf::Color outlineColor = sf::Color::White);
    bool isClicked(sf::Vector2f mousePosition) override;
    void draw(sf::RenderWindow &window) override;
    ~ButtonLevier() = default;
};