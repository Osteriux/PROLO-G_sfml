#include "item_factory.hpp"
#include "../game_object/static/pickup/mine.hpp"
#include "../game_object/static/pickup/battery.hpp"
#include "../game_object/static/pickup/bomb.hpp"
#include "../game_object/static/pickup/detector.hpp"
#include "../utils/logger/logger.hpp"

std::unique_ptr<Pickup> ItemFactory::createPickup(int type, int x, int y)
{
    Logger::log("Creating pickup " + std::to_string(type) + " at : " + std::to_string(x) + "," + std::to_string(y), Logger::INFO);
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
        Logger::log("Invalid pickup type: " + std::to_string(type), Logger::ERROR);
        throw std::invalid_argument("Invalid pickup type");
    }
}

std::unique_ptr<Lever> ItemFactory::createLever(sf::Color color, int x, int y, int doorId, int nb)
{
    return std::make_unique<Lever>(color, x, y, doorId, nb);
}