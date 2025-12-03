#pragma once
#include "../dynamic_game_object.hpp"
#include "inventory.hpp"

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
