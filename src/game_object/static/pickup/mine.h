#pragma once
#include "pickup.h"

class Mine : public Pickup
{
private:
    bool active;

public:
    Mine(int x, int y);
    std::string getDescription() const override;
    void action(DynamicGameObject *user) override;
    ~Mine() = default;
};