#pragma once
#include <memory>
#include "../game_object/static/pickup/pickup.h"
#include "../game_object/static/interactible/lever.h"

class PickupFactory
{
public:
    static std::unique_ptr<Pickup> createPickup(int x, int y, int type);
    static std::unique_ptr<Lever> createLever(sf::Color color, int x, int y, int doorId, int nb);
};