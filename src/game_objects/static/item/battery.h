#pragma once
#include "item.h"

class Battery : public Item
{
public:
    Battery(int x, int y);
    std::string getDescription() const override;
    void action(DynamicGameObject* user) override;
    ~Battery() = default;
};