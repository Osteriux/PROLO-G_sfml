#pragma once
#include <memory>
#include "../game_objects/static/item/item.h"
#include "../game_objects/static/item/mine.h"
#include "../game_objects/static/item/battery.h"
#include "../game_objects/static/item/bomb.h"
#include "../game_objects/static/item/detector.h"
#include "../game_objects/static/lever/lever.h"

class ItemFactory
{
public:
    static std::unique_ptr<Item> createItem(int x, int y, int type);
    static std::unique_ptr<Lever> createLever(sf::Color color, int x, int y, int doorId, int nb);
};