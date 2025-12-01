#include "item_factory.h"
#include "../game_object/static/pickup/mine.h"
#include "../game_object/static/pickup/battery.h"
#include "../game_object/static/pickup/bomb.h"
#include "../game_object/static/pickup/detector.h"

std::unique_ptr<Pickup> PickupFactory::createPickup(int type, int x, int y)
{
    std::cout << "Creating pickup " << type << " at : " << x << "," << y << std::endl;
    Pickup::PickupType pickupType = Pickup::idToPickupType(type);
    switch (pickupType)
    {
    case Pickup::PickupType::MINE:
        return std::make_unique<Mine>(x, y);
    case Pickup::PickupType::BATTERY:
        return std::make_unique<Battery>(x, y);
    case Pickup::PickupType::BOMB:
        return std::make_unique<Bomb>(x, y);
    case Pickup::PickupType::DETECTOR:
        return std::make_unique<Detector>(x, y);
    default:
        throw std::invalid_argument("Invalid pickup type");
    }
}

std::unique_ptr<Lever> PickupFactory::createLever(sf::Color color, int x, int y, int doorId, int nb)
{
    return std::make_unique<Lever>(color, x, y, doorId, nb);
}