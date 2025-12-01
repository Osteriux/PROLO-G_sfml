#pragma once
#include "../../static/item/item.h"
#include <unordered_map>

class Inventory
{
    std::unordered_map<Item::ItemType, int> items;
public:
    Inventory();
    int getQuantity(Item::ItemType item);
    void addItem(Item::ItemType item);
    void removeItem(Item::ItemType item);
    ~Inventory() = default;
};
