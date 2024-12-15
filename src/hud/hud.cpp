#include "hud.h"

HUD::HUD(sf::Vector2u origin, sf::Vector2u size, Joueur* joueur)
    : origin(origin), size(size), joueur(joueur)
{
    if (!font.loadFromFile("assets/fonts/arial.ttf"))
    {
        std::cerr << "Error loading font : assets/fonts/arial.ttf" << std::endl;
    }
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color::White);
    outline.setOutlineThickness(2);
    outline.setPosition(sf::Vector2f(origin));
    outline.setSize(sf::Vector2f(size.x, size.y));
}

void HUD::update(float dt)
{
}

void HUD::draw(sf::RenderWindow &window)
{
    window.draw(outline);
}