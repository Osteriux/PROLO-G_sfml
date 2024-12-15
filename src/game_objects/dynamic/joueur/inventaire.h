#pragma once
#include "../../static/item/item.h"
#include <unordered_map>

class Inventaire
{
    std::unordered_map<Item::ItemType, int> items;
public:
    Inventaire() = default;
    void addItem(Item::ItemType item);
    void removeItem(Item::ItemType item);
    ~Inventaire() = default;
};
