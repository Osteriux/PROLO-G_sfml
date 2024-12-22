#pragma once
#include "monstre.h"

class Chien : public Monstre
{
public:
    Chien(sf::Vector2f position, GameManager* gameManager);
    ~Chien() = default;
};