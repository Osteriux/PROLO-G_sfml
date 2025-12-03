#pragma once
#include "pickup.hpp"

class Detector : public Pickup
{
private:
    int charge;
    bool active;

public:
    Detector(int x, int y);
    std::string getDescription() const override;
    void action(DynamicGameObject *user) override;
    ~Detector() = default;
};