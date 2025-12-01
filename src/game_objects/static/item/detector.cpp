#include "detector.h"

Detector::Detector(int x, int y)
    : Item(std::make_unique<MultiTexture>(Item::texturePath(Item::DETECTOR), 2, 3, std::vector({3, 3})), x, y)
{
    type = ItemType::DETECTOR;
    charge = 0;
    active = false;
}

std::string Detector::getDescription() const
{
    return "Detector";
}

void Detector::action(DynamicGameObject* user)
{
    std::cout << "Detector action" << std::endl;
}