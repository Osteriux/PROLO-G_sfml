#pragma once
#include <SFML/Graphics.hpp>
#include "../game_objects/dynamic/joueur/joueur.h"

class HUD {
private:
    sf::RectangleShape outline;
    Joueur* joueur;
    sf::Vector2u origin;
    sf::Vector2u size;
    sf::Font font;
public:
    HUD(sf::Vector2u origin, sf::Vector2u size, Joueur* joueur);
    void update(float dt);
    void draw(sf::RenderWindow &window);
    ~HUD() = default;
};
