#include "hud.h"

HUD::HUD(sf::Vector2f origin, Joueur* joueur)
    : joueur(joueur), origin(origin)
{
    if (!font.loadFromFile("assets/fonts/arial.ttf"))
    {
        std::cerr << "Error loading font : assets/fonts/arial.ttf" << std::endl;
    }
}

void HUD::update(float dt)
{
}

void HUD::draw(sf::RenderWindow &window)
{
}