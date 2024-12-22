#pragma once
#include "item.h"

class Batterie : public Item
{
public:
    Batterie(int x, int y, GameManager* gameManager);
    std::string getDescription() override;
    void action(DynamicGameObject* user) override;
    ~Batterie() = default;
};