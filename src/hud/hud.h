#pragma once
#include <SFML/Graphics.hpp>
#include "../game_objects/dynamic/joueur/joueur.h"

class HUD {
private:
    Joueur* joueur;
    sf::Vector2f origin;
    sf::Font font;
public:
    HUD(sf::Vector2f origin, Joueur* joueur);
    void update(float dt);
    void draw(sf::RenderWindow &window);
    ~HUD() = default;
};
