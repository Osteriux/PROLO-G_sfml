#pragma once
#include "../../static/pickup/pickup.hpp"
#include <unordered_map>

class Inventory
{
private:
    std::unordered_map<Pickup::PickupType, int> pickups;

public:
    Inventory();
    int getQuantity(Pickup::PickupType pickup);
    void addPickup(Pickup::PickupType pickup);
    void removePickup(Pickup::PickupType pickup);
    ~Inventory() = default;
};
