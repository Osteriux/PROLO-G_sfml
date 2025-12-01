#pragma once
#include "monster.h"

class Dog : public Monster
{
public:
    Dog(int x, int y);
    std::string getDescription() const override;
    ~Dog() = default;
};