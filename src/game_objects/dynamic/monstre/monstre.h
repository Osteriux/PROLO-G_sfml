#pragma once
#include "../dynamic_game_object.h"

class Monstre : public DynamicGameObject
{
public:
    Monstre(sf::Vector2f position, Carte* carte, int health, float speed);
    ~Monstre() = default;
};