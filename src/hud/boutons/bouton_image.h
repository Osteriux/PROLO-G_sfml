#pragma once
#include "bouton_base.h"
#include <memory>

class ButtonImage : public ButtonBase {
private:
    sf::Texture texture;
    sf::Sprite sprite;
public:
    ButtonImage(sf::Vector2f position, sf::Vector2f size, std::string texturePath, sf::Color backgroundColor = sf::Color::Transparent);
    void draw(sf::RenderWindow &window) override;
    ~ButtonImage() = default;
};
