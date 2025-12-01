#pragma once
#include "pickup.h"

class Battery : public Pickup
{
public:
    Battery(int x, int y);
    std::string getDescription() const override;
    void action(DynamicGameObject *user) override;
    ~Battery() = default;
};