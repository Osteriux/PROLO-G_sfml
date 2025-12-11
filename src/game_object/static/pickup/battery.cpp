#include "battery.hpp"
#include "../../dynamic/player/player.hpp"
#include "../../../utils/logger/logger.hpp"

Battery::Battery(int x, int y)
    : Pickup(std::make_unique<MultiTexture>(Pickup::texturePath(Pickup::BATTERY), 1), x, y)
{
    type = PickupType::BATTERY;
}

std::string Battery::getDescription() const
{
    return "Battery";
}

void Battery::action(DynamicGameObject *user)
{
    Logger::log("Battery action", Logger::INFO);
}
