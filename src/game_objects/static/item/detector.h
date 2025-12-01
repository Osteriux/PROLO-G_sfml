#pragma once
#include "item.h"

class Detector : public Item
{
private:
    int charge;
    bool active;
public:
    Detector(int x, int y);
    std::string getDescription() const override;
    void action(DynamicGameObject* user) override;
    ~Detector() = default;
};