#include "inventaire.h"

Inventaire::Inventaire()
{
    for (auto item : Item::getAllItemTypes())
    {
        items[item] = 0;
    }
}

int Inventaire::getQuantity(Item::ItemType item)
{
    return items[item];
}

void Inventaire::addItem(Item::ItemType item)
{
    items[item]++;
}

void Inventaire::removeItem(Item::ItemType item)
{
    items[item]--;
}