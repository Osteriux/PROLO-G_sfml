#pragma once
#include "monstre.h"

class Chien : public Monstre
{
public:
    Chien(GameManager *gameManager, int x, int y);
    std::string getDescription() const override;
    ~Chien() = default;
};