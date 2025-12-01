#include "detector.h"

Detector::Detector(int x, int y)
    : Pickup(std::make_unique<MultiTexture>(Pickup::texturePath(Pickup::DETECTOR), 2, 3, std::vector({3, 3})), x, y)
{
    type = PickupType::DETECTOR;
    charge = 0;
    active = false;
}

std::string Detector::getDescription() const
{
    return "Detector";
}

void Detector::action(DynamicGameObject *user)
{
    std::cout << "Detector action" << std::endl;
}