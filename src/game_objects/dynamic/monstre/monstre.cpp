#include "monstre.h"

Monstre::Monstre(sf::Vector2f position, Carte* carte, int health, float speed)
    : DynamicGameObject(health, speed, std::make_unique<MultiTexture>("assets/dynamic/CHIEN.png", 1), carte, position.x, position.y)
{
}