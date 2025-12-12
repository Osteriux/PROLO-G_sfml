#include "lever.hpp"
#include "../../../map/case.hpp"
#include "../../../manager/game_manager.hpp"
#include "../../../manager/game_event.hpp"
#include "../../../utils/logger/logger.hpp"

Lever::Lever(sf::Color color, int x, int y, int doorId, int nb)
    : Interactible(createRect(color, nb), x, y), activated(false), doorId(doorId), color(color)
{
    type = InteractibleType::LEVER;
}

void Lever::interact(DynamicGameObject *user)
{
    if (currCase == nullptr)
    {
        Logger::log("Lever::interact: currCase is nullptr", Logger::ERROR);
        return;
    }

    activated = !activated;
    std::string message = "Lever at (" + std::to_string(currCase->getX()) + ", " + std::to_string(currCase->getY()) + ") ";
    if (activated)
    {
        Logger::log("Door " + std::to_string(doorId) + " opened", Logger::INFO);
        message += "activated.";
    }
    else
    {
        Logger::log("Door " + std::to_string(doorId) + " closed", Logger::INFO);
        message += "deactivated.";
    }
    GameManager::getInstance().addLogMessage(message);

    // Emit lever toggled event
    LeverToggledEvent event(doorId, activated, currCase->getX(), currCase->getY());
    GameManager::getInstance().getEventSystem().dispatch(event);
}

sf::Color Lever::getColor() const
{
    return color;
}

bool Lever::isActivated() const
{
    return activated;
}

std::string Lever::getDescription() const
{
    return "Lever";
}

std::unique_ptr<MultiTexture> Lever::createRect(sf::Color color, int nb)
{
    if (nb > 20)
    {
        Logger::log("too many levers on the same case: must be less than 20", Logger::ERROR);
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
    Logger::log("Creating lever " + std::to_string(nb) + " at : " + std::to_string(pos.x) + " " + std::to_string(pos.y), Logger::INFO);
    return std::make_unique<MultiTexture>(color, 3, 3, pos);
}