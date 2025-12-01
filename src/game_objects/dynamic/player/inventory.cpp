#include "inventory.h"

Inventory::Inventory()
{
    for (auto item : Item::getAllItemTypes())
    {
        items[item] = 0;
    }
}

int Inventory::getQuantity(Item::ItemType item)
{
    return items[item];
}

void Inventory::addItem(Item::ItemType item)
{
    items[item]++;
}

void Inventory::removeItem(Item::ItemType item)
{
    items[item]--;
}