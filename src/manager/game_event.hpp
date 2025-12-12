#pragma once
#include <string>
#include <memory>
#include "../game_object/static/pickup/pickup.hpp"
#include "../map/direction.hpp"

// Base event class
class GameEvent
{
public:
    enum class Type
    {
        NONE, // for dummy events
        PLAYER_DAMAGED,
        PLAYER_HEALED,
        PLAYER_INVENTORY_CHANGED,
        PLAYER_MOVED,
        PLAYER_CONTEXT_CHANGED,
        ITEM_PICKED_UP,
        ITEM_USED,
        LEVER_TOGGLED,
        DOOR_OPENED,
        DOOR_CLOSED,
        MONSTER_SPAWNED,
        MONSTER_DEFEATED,
        HUD_ACTION
    };

    virtual ~GameEvent() = default;
    virtual Type getType() const = 0;
};

// Player movement event
class PlayerMovedEvent : public GameEvent
{
private:
    Direction::Dir direction;
    int fromX, fromY;
    int toX, toY;
    bool success;

public:
    PlayerMovedEvent(Direction::Dir dir, int fx, int fy, int tx, int ty, bool success)
        : direction(dir), fromX(fx), fromY(fy), toX(tx), toY(ty), success(success) {}

    Type getType() const override { return Type::PLAYER_MOVED; }
    Direction::Dir getDirection() const { return direction; }
    int getFromX() const { return fromX; }
    int getFromY() const { return fromY; }
    int getToX() const { return toX; }
    int getToY() const { return toY; }
    bool wasSuccessful() const { return success; }
};

// Player health change events
class PlayerDamagedEvent : public GameEvent
{
private:
    int damage;
    int currentHealth;
    std::string source;

public:
    PlayerDamagedEvent(int dmg, int health, const std::string &src)
        : damage(dmg), currentHealth(health), source(src) {}

    Type getType() const override { return Type::PLAYER_DAMAGED; }
    int getDamage() const { return damage; }
    int getCurrentHealth() const { return currentHealth; }
    const std::string &getSource() const { return source; }
};

class PlayerHealedEvent : public GameEvent
{
private:
    int healing;
    int currentHealth;

public:
    PlayerHealedEvent(int heal, int health)
        : healing(heal), currentHealth(health) {}

    Type getType() const override { return Type::PLAYER_HEALED; }
    int getHealing() const { return healing; }
    int getCurrentHealth() const { return currentHealth; }
};

// Player inventory event
class PlayerInventoryChangedEvent : public GameEvent
{
private:
    int mineCount;
    int batteryCount;
    int bombCount;
    int detectorCount;

public:
    PlayerInventoryChangedEvent(int mine, int battery, int bomb, int detector)
        : mineCount(mine), batteryCount(battery), bombCount(bomb), detectorCount(detector) {}

    Type getType() const override { return Type::PLAYER_INVENTORY_CHANGED; }
    int getMineCount() const { return mineCount; }
    int getBatteryCount() const { return batteryCount; }
    int getBombCount() const { return bombCount; }
    int getDetectorCount() const { return detectorCount; }
};

// Player context event (case changed - new pickups/interactibles available)
class PlayerContextChangedEvent : public GameEvent
{
private:
    int caseX, caseY;
    std::vector<Pickup::PickupType> availablePickups;

public:
    PlayerContextChangedEvent(int x, int y, const std::vector<Pickup::PickupType> &pickups)
        : caseX(x), caseY(y), availablePickups(pickups) {}
    Type getType() const override { return Type::PLAYER_CONTEXT_CHANGED; }
    int getCaseX() const { return caseX; }
    int getCaseY() const { return caseY; }
    const std::vector<Pickup::PickupType> &getAvailablePickups() const { return availablePickups; }
};

// Item events
class ItemPickedUpEvent : public GameEvent
{
private:
    Pickup::PickupType itemType;
    int x, y;

public:
    ItemPickedUpEvent(Pickup::PickupType type, int x, int y)
        : itemType(type), x(x), y(y) {}

    Type getType() const override { return Type::ITEM_PICKED_UP; }
    Pickup::PickupType getItemType() const { return itemType; }
    int getX() const { return x; }
    int getY() const { return y; }
};

class ItemUsedEvent : public GameEvent
{
private:
    Pickup::PickupType itemType;
    bool success;

public:
    ItemUsedEvent(Pickup::PickupType type, bool success)
        : itemType(type), success(success) {}

    Type getType() const override { return Type::ITEM_USED; }
    Pickup::PickupType getItemType() const { return itemType; }
    bool wasSuccessful() const { return success; }
};

// Lever event
class LeverToggledEvent : public GameEvent
{
private:
    int doorId;
    bool activated;
    int x, y;

public:
    LeverToggledEvent(int doorId, bool activated, int x, int y)
        : doorId(doorId), activated(activated), x(x), y(y) {}

    Type getType() const override { return Type::LEVER_TOGGLED; }
    int getDoorId() const { return doorId; }
    bool isActivated() const { return activated; }
    int getX() const { return x; }
    int getY() const { return y; }
};

// Door events
class DoorOpenedEvent : public GameEvent
{
private:
    int doorId;

public:
    DoorOpenedEvent(int id) : doorId(id) {}
    Type getType() const override { return Type::DOOR_OPENED; }
    int getDoorId() const { return doorId; }
};

class DoorClosedEvent : public GameEvent
{
private:
    int doorId;

public:
    DoorClosedEvent(int id) : doorId(id) {}
    Type getType() const override { return Type::DOOR_CLOSED; }
    int getDoorId() const { return doorId; }
};

// HUD Action event - emitted when user interacts with HUD
class HUDActionEvent : public GameEvent
{
public:
    enum class ActionType
    {
        NONE, // Placeholder
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN,
        USE_RADAR,
        USE_MINE,
        USE_BATTERY,
        USE_BOMB,
        USE_DETECTOR,
        PICKUP_ITEM,
        INTERACT_LEVER
    };

private:
    ActionType action;
    int index; // For pickups/levers: which one (by index)
    class Lever* lever; // Direct pointer to lever (for INTERACT_LEVER action)

public:
    HUDActionEvent(ActionType act, int idx = -1, class Lever* leverPtr = nullptr)
        : action(act), index(idx), lever(leverPtr) {}

    Type getType() const override { return Type::HUD_ACTION; }
    ActionType getAction() const { return action; }
    int getIndex() const { return index; }
    class Lever* getLever() const { return lever; }
};
