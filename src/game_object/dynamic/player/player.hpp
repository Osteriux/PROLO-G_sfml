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
    
    // Action methods that emit events
    bool usePickup(Pickup::PickupType type);
    void takeDamage(int damage, const std::string &source);
    void heal(int amount);
    void interactWithLever(class Lever *lever);
    
    // Event emission helpers
    void emitInventoryChanged();
    void emitContextChanged();
    
    ~Player() = default;
};
