#pragma once
#include "item.h"

class Bombe : public Item
{
private:
    bool active;
public:
    Bombe(int x, int y, GameManager* gameManager);
    std::string getDescription() override;
    void action(DynamicGameObject* user) override;
    ~Bombe() = default;
};