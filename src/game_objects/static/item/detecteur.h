#pragma once
#include "item.h"

class Detecteur : public Item
{
private:
    int charge;
    bool active;
public:
    Detecteur(int x, int y, GameManager* gameManager);
    std::string getDescription() const override;
    void action(DynamicGameObject* user) override;
    ~Detecteur() = default;
};