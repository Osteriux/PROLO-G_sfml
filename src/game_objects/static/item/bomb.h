#pragma once
#include "item.h"

class Bomb : public Item
{
private:
    bool active;
public:
    Bomb(int x, int y);
    std::string getDescription() const override;
    void action(DynamicGameObject* user) override;
    ~Bomb() = default;
};