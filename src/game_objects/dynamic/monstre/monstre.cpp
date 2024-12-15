#include "monstre.h"

Monstre::Monstre(sf::Vector2f position, Carte* carte, int health, float speed)
    : DynamicGameObject(health, speed, std::make_unique<MultiTexture>(sf::Color::Red, 16, 16), carte, position.x, position.y)
{
}