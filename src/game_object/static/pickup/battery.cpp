#include "battery.hpp"
#include "../../dynamic/player/player.hpp"

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
    std::cout << "Battery action" << std::endl;
}
