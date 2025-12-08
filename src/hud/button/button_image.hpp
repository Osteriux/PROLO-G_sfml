#pragma once
#include "button_base.hpp"
#include <memory>

class ButtonImage : public ButtonBase {
private:
    sf::Texture texture;
    sf::Sprite sprite;
public:
    ButtonImage(sf::Vector2f position, sf::Vector2f size, std::string texturePath, sf::Color backgroundColor = sf::Color::Transparent);
    void draw(sf::RenderWindow &window) override;
    void setPosition(sf::Vector2f newPosition);
    ~ButtonImage() = default;
};
