#pragma once
#include "../dynamic_game_object.h"
#include "inventory.h"

class GameManager;

class Player : public DynamicGameObject
{
private:
    Inventory inventory;
public:
    Player(int x, int y, int health);
    Inventory& getInventory();
    std::string getDescription() const override;
    void move(Direction::Dir direction);
    ~Player() = default;
};
