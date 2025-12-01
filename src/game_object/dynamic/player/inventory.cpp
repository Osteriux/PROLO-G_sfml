#include "inventory.h"

Inventory::Inventory()
{
    for (auto pickup : Pickup::getAllPickupTypes())
    {
        pickups[pickup] = 0;
    }
}

int Inventory::getQuantity(Pickup::PickupType pickup)
{
    return pickups[pickup];
}

void Inventory::addPickup(Pickup::PickupType pickup)
{
    pickups[pickup]++;
}

void Inventory::removePickup(Pickup::PickupType pickup)
{
    pickups[pickup]--;
}