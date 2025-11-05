#pragma once
#include "item.h"

class Mine : public Item
{
private:
    bool active;
public:
    Mine(int x, int y, GameManager* gameManager);
    std::string getDescription() const override;
    void action(DynamicGameObject* user) override;
    ~Mine() = default;
};