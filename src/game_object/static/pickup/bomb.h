#pragma once
#include "pickup.h"

class Bomb : public Pickup
{
private:
    bool active;

public:
    Bomb(int x, int y);
    std::string getDescription() const override;
    void action(DynamicGameObject *user) override;
    ~Bomb() = default;
};