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
public:
    Porte(sf::Color color, Direction::Dir dir);
    bool estOuverte();
    void ouvrir();
    void fermer();
    sf::Color getColor();
    void draw(sf::RenderTarget &target);
    ~Porte() = default;
};
