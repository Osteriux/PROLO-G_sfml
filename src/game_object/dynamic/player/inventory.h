#pragma once
#include "../../static/pickup/pickup.h"
#include <unordered_map>

class Inventory
{
    std::unordered_map<Pickup::PickupType, int> pickups;

public:
    Inventory();
    int getQuantity(Pickup::PickupType pickup);
    void addPickup(Pickup::PickupType pickup);
    void removePickup(Pickup::PickupType pickup);
    ~Inventory() = default;
};
