#pragma once
#include "../static_game_object.h"

class GameManager;

class Player;

class Pickup : public StaticGameObject
{
public:
    enum class PickupType
    {
        MINE,
        BATTERY,
        BOMB,
        DETECTOR
    };
    static const PickupType MINE = PickupType::MINE;
    static const PickupType BATTERY = PickupType::BATTERY;
    static const PickupType BOMB = PickupType::BOMB;
    static const PickupType DETECTOR = PickupType::DETECTOR;
    static std::string pickupTypeToString(PickupType type);
    static PickupType stringToPickupType(std::string type);
    static int pickupTypeToId(PickupType type);
    static PickupType idToPickupType(int id);
    static std::vector<PickupType> getAllPickupTypes();

    Pickup(std::unique_ptr<MultiTexture> tex, int x, int y);
    void pickup(Player *user);
    ~Pickup() = default;

protected:
    PickupType type;
    static std::string texturePath(PickupType type);
};