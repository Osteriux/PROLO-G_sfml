#include "pickup.hpp"
#include "../../dynamic/player/player.hpp"
#include "../../../manager/game_manager.hpp"
#include "../../../utils/logger/logger.hpp"

Pickup::Pickup(std::unique_ptr<MultiTexture> tex, int x, int y)
    : StaticGameObject(std::move(tex), x, y)
{
}

void Pickup::pickup(Player *user)
{
    user->getInventory().addPickup(type);
}

Pickup::PickupType Pickup::getType() const
{
    return type;
}

std::vector<Pickup::PickupType> Pickup::getAllPickupTypes()
{
    return {PickupType::MINE, PickupType::BATTERY, PickupType::BOMB, PickupType::DETECTOR};
}

std::string Pickup::pickupTypeToString(PickupType type)
{
    switch (type)
    {
    case PickupType::MINE:
        return "MINE";
    case PickupType::BATTERY:
        return "BATTERY";
    case PickupType::BOMB:
        return "BOMB";
    case PickupType::DETECTOR:
        return "DETECTOR";
    default:
        Logger::log("Invalid pickup type", Logger::ERROR);
        throw std::invalid_argument("Invalid pickup type");
    }
}

Pickup::PickupType Pickup::stringToPickupType(std::string type)
{
    if (type == "MINE")
        return PickupType::MINE;
    else if (type == "BATTERY")
        return PickupType::BATTERY;
    else if (type == "BOMB")
        return PickupType::BOMB;
    else if (type == "DETECTOR")
        return PickupType::DETECTOR;
    else
        Logger::log("Invalid pickup type: " + type, Logger::ERROR);
    throw std::invalid_argument("Invalid pickup type");
}

int Pickup::pickupTypeToId(PickupType type)
{
    switch (type)
    {
    case PickupType::MINE:
        return 0;
    case PickupType::BATTERY:
        return 1;
    case PickupType::BOMB:
        return 2;
    case PickupType::DETECTOR:
        return 3;
    default:
        Logger::log("Invalid pickup id", Logger::ERROR);
        throw std::invalid_argument("Invalid pickup id");
    }
}

Pickup::PickupType Pickup::idToPickupType(int id)
{
    switch (id)
    {
    case 0:
        return PickupType::MINE;
    case 1:
        return PickupType::BATTERY;
    case 2:
        return PickupType::BOMB;
    case 3:
        return PickupType::DETECTOR;
    default:
        Logger::log("Invalid pickup id: " + std::to_string(id), Logger::ERROR);
        throw std::invalid_argument("Invalid pickup id");
    }
}

std::string Pickup::texturePath(PickupType type, bool hud)
{
    std::string basePath = hud ? "assets/hud/" : "assets/static/";
    return basePath + pickupTypeToString(type) + ".png";
}
