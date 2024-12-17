#pragma once
#include <sstream>
#include "../animations/multi_texture.h"
#include "direction.h"

class GameObject;

class Porte {
private:
    MultiTexture texture;
    sf::RectangleShape bg;
    bool ouverte;
    Direction::Dir dir;
    sf::Color color;
    std::string texturePath(Direction::Dir dir);
public:
    Porte(sf::Color color, Direction::Dir dir, sf::Vector2f position);
    bool estOuverte();
    void ouvrir();
    void fermer();
    sf::Color getColor();
    void setPosition(sf::Vector2f position);
    void setScale(sf::Vector2f scale);
    void draw(sf::RenderTarget &target);
    ~Porte() = default;
};
