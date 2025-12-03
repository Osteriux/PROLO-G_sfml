#pragma once
#include <memory>
#include "../game_object/static/pickup/pickup.hpp"
#include "../game_object/static/interactible/lever.hpp"

class ItemFactory
{
public:
    static std::unique_ptr<Pickup> createPickup(int x, int y, int type);
    static std::unique_ptr<Lever> createLever(sf::Color color, int x, int y, int doorId, int nb);
};