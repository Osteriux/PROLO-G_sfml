#include "lever.hpp"
#include "../../../map/case.hpp"
#include "../../../manager/game_manager.hpp"

Lever::Lever(sf::Color color, int x, int y, int doorId, int nb)
    : Interactible(createRect(color, nb), x, y), activated(false), doorId(doorId), color(color)
{
    type = InteractibleType::LEVER;
}

void Lever::interact(DynamicGameObject *user)
{
    activated = !activated;
    std::string message = "Lever at (" + std::to_string(currCase->getX()) + ", " + std::to_string(currCase->getY()) + ") ";
    if (activated)
    {
        std::cout << "Door " << doorId << " opened" << std::endl;
        message += "activated.";
    }
    else
    {
        std::cout << "Door " << doorId << " closed" << std::endl;
        message += "deactivated.";
    }
    GameManager::getInstance().addLogMessage(message);
}

sf::Color Lever::getColor() const
{
    return color;
}

std::string Lever::getDescription() const
{
    return "Lever";
}

std::unique_ptr<MultiTexture> Lever::createRect(sf::Color color, int nb)
{
    if (nb > 20)
    {
        throw std::invalid_argument("too many levers on the same case: must be less than 20");
    }
    sf::Vector2f pos(7, 7);
    if (nb > 10)
    {
        pos.x = 21;
    }
    if ((nb / 5) % 2 == 1)
    {
        pos.x += 3;
    }
    pos.y += 3 * (nb % 5);
    std::cout << "Creating lever " << nb << " at : " << pos.x << " " << pos.y << std::endl;
    return std::make_unique<MultiTexture>(color, 3, 3, pos);
}