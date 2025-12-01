#pragma once
#include "button_base.h"

class ButtonText : public ButtonBase {
private:
    sf::Text text;
    sf::Font font;
public:
    ButtonText(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Color backgroundColor = sf::Color::White, sf::Color textColor = sf::Color::Black);
    void draw(sf::RenderWindow &window) override;
    ~ButtonText() = default;
};
