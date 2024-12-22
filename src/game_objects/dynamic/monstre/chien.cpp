#include "chien.h"

Chien::Chien(sf::Vector2f position, GameManager* gameManager)
    : Monstre(position, gameManager, Monstre::monstreTypeToString(Monstre::CHIEN), 100, 0.1)
{
}