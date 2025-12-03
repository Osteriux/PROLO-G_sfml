#include "../../../manager/game_manager.hpp"
#include "../../../manager/game_event.hpp"
#include "player.hpp"
#include "../../static/interactible/lever.hpp"

Player::Player(int x, int y, int health)
    : DynamicGameObject(health, 1, std::make_unique<MultiTexture>("assets/dynamic/PLAYER.png", 1), x, y), inventory()
{
}

Inventory& Player::getInventory()
{
    return inventory;
}

std::string Player::getDescription() const
{
    return "Player";
}

void Player::move(Direction::Dir direction)
{
    int fromX = currCase->getX();
    int fromY = currCase->getY();
    
    DynamicGameObject::move(direction);
    
    int toX = currCase->getX();
    int toY = currCase->getY();
    bool success = (fromX != toX || fromY != toY);
    
    // Emit move event
    PlayerMovedEvent event(direction, fromX, fromY, toX, toY, success);
    GameManager::getInstance().getEventSystem().dispatch(event);
    
    // If move was successful, context changed (new case)
    if (success)
    {
        emitContextChanged();
    }
}

bool Player::usePickup(Pickup::PickupType type)
{
    int quantity = inventory.getQuantity(type);
    if (quantity <= 0)
    {
        ItemUsedEvent event(type, false);
        GameManager::getInstance().getEventSystem().dispatch(event);
        return false;
    }
    
    // Remove from inventory
    inventory.removePickup(type);
    
    // Execute pickup action
    // TODO: Implement actual pickup effects (mine placement, radar use, etc.)
    
    // Emit success event
    ItemUsedEvent event(type, true);
    GameManager::getInstance().getEventSystem().dispatch(event);
    
    // Emit inventory changed
    emitInventoryChanged();
    
    return true;
}

void Player::takeDamage(int damage, const std::string &source)
{
    health -= damage;
    if (health < 0)
        health = 0;
    
    PlayerDamagedEvent event(damage, health, source);
    GameManager::getInstance().getEventSystem().dispatch(event);
    
    if (health <= 0)
    {
        // TODO: Handle player death
        GameManager::getInstance().addLogMessage("Player has been defeated!");
    }
}

void Player::heal(int amount)
{
    health += amount;
    // TODO: Add max health cap if needed
    
    PlayerHealedEvent event(amount, health);
    GameManager::getInstance().getEventSystem().dispatch(event);
}

void Player::interactWithLever(class Lever *lever)
{
    if (lever != nullptr)
    {
        lever->interact(this);
        // Lever will emit its own event
    }
}

void Player::emitInventoryChanged()
{
    PlayerInventoryChangedEvent event(
        inventory.getQuantity(Pickup::PickupType::MINE),
        inventory.getQuantity(Pickup::PickupType::BATTERY),
        inventory.getQuantity(Pickup::PickupType::BOMB),
        inventory.getQuantity(Pickup::PickupType::DETECTOR)
    );
    GameManager::getInstance().getEventSystem().dispatch(event);
}

void Player::emitContextChanged()
{
    std::vector<Pickup::PickupType> availablePickups;
    for (const auto &pickup : currCase->getPickups())
    {
        availablePickups.push_back(pickup->getType());
    }
    
    int leverCount = 0;
    for (const auto &interactible : currCase->getInteractibles())
    {
        if (interactible->getType() == Interactible::InteractibleType::LEVER)
        {
            leverCount++;
        }
    }
    
    PlayerContextChangedEvent event(
        currCase->getX(),
        currCase->getY(),
        availablePickups,
        leverCount
    );
    GameManager::getInstance().getEventSystem().dispatch(event);
}