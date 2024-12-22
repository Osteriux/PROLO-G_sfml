#pragma once
#include <memory>
#include "../manager/game_manager.h"
#include "../game_objects/static/item/item.h"
#include "../game_objects/static/item/mine.h"
#include "../game_objects/static/item/batterie.h"
#include "../game_objects/static/item/bombe.h"
#include "../game_objects/static/item/detecteur.h"

class ItemFactory
{
public:
    static std::unique_ptr<Item> createItem(int x, int y, int type, GameManager* gameManager);
};