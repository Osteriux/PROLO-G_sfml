#include "battery.h"
#include "../../dynamic/player/player.h"

Battery::Battery(int x, int y)
    : Item(std::make_unique<MultiTexture>(Item::texturePath(Item::BATTERY), 1), x, y)
{
    type = ItemType::BATTERY;
}

std::string Battery::getDescription() const
{
    return "Battery";
}

void Battery::action(DynamicGameObject* user)
{
    std::cout << "Battery action" << std::endl;
}
