#include "log.hpp"
#include "../manager/game_event.hpp"
#include "../game_object/static/pickup/pickup.hpp"
#include "../map/direction.hpp"
#include "../utils/logger/logger.hpp"

Log::Log(int maxMessages, sf::Vector2u origin, sf::Vector2u size)
    : maxMessages(maxMessages), origin(origin), rect(sf::FloatRect(origin.x, origin.y, size.x, size.y))
{
    if (!font.loadFromFile("assets/font/arial.ttf"))
    {
        Logger::log("Error loading font : assets/font/arial.ttf", Logger::ERROR);
    }
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color::White);
    outline.setOutlineThickness(2);
    outline.setPosition(sf::Vector2f(origin));
    outline.setSize(sf::Vector2f(size.x, size.y));
}

void Log::init()
{
    // Subscribe to all game events for logging
    GameEventSystem::getInstance().subscribe(GameEvent::Type::PLAYER_MOVED, this);
    GameEventSystem::getInstance().subscribe(GameEvent::Type::PLAYER_DAMAGED, this);
    GameEventSystem::getInstance().subscribe(GameEvent::Type::PLAYER_HEALED, this);
    GameEventSystem::getInstance().subscribe(GameEvent::Type::ITEM_PICKED_UP, this);
    GameEventSystem::getInstance().subscribe(GameEvent::Type::ITEM_USED, this);
    GameEventSystem::getInstance().subscribe(GameEvent::Type::LEVER_TOGGLED, this);
}

void Log::scrollUp()
{
    for (sf::Text &message : messages)
    {
        message.move(0, -20);
    }
}

void Log::scrollDown()
{
    for (sf::Text &message : messages)
    {
        message.move(0, 20);
    }
}

void Log::addMessage(std::string message)
{
    if (messages.size() == maxMessages)
    {
        messages.erase(messages.begin());
    }
    messages.push_back(sf::Text(message, font));
}

void Log::draw(sf::RenderWindow &window)
{
    window.draw(outline);
    sf::View originalView = window.getView();
    sf::View view(sf::FloatRect(rect.left, rect.top, rect.width, rect.height));
    window.setView(view);
    for (sf::Text &message : messages)
    {
        window.draw(message);
    }
    window.setView(originalView);
}

Log::~Log()
{
    // Note: GameManager::destroy() handles unsubscription before destroying event system
    // This is just a safety check if Log is destroyed independently
}

void Log::onEvent(const GameEvent &event)
{
    std::string message;

    switch (event.getType())
    {
    case GameEvent::Type::PLAYER_MOVED:
    {
        const auto &moveEvent = static_cast<const PlayerMovedEvent &>(event);
        if (moveEvent.wasSuccessful())
        {
            message = "Player moved " + Direction::directionToString(moveEvent.getDirection());
        }
        else
        {
            message = "Cannot move " + Direction::directionToString(moveEvent.getDirection());
        }
        break;
    }
    case GameEvent::Type::PLAYER_DAMAGED:
    {
        const auto &damageEvent = static_cast<const PlayerDamagedEvent &>(event);
        message = "Player took " + std::to_string(damageEvent.getDamage()) +
                  " damage from " + damageEvent.getSource();
        break;
    }
    case GameEvent::Type::PLAYER_HEALED:
    {
        const auto &healEvent = static_cast<const PlayerHealedEvent &>(event);
        message = "Player healed " + std::to_string(healEvent.getHealing()) + " HP";
        break;
    }
    case GameEvent::Type::ITEM_PICKED_UP:
    {
        const auto &pickupEvent = static_cast<const ItemPickedUpEvent &>(event);
        message = "Picked up item"; // Could add item name lookup
        break;
    }
    case GameEvent::Type::ITEM_USED:
    {
        const auto &useEvent = static_cast<const ItemUsedEvent &>(event);
        if (useEvent.wasSuccessful())
        {
            message = "Used item"; // Could add item name lookup
        }
        else
        {
            message = "Cannot use item - none in inventory";
        }
        break;
    }
    case GameEvent::Type::LEVER_TOGGLED:
    {
        const auto &leverEvent = static_cast<const LeverToggledEvent &>(event);
        message = "Lever " + std::string(leverEvent.isActivated() ? "activated" : "deactivated");
        break;
    }
    default:
        return; // Don't log unknown events
    }

    if (!message.empty())
    {
        addMessage(message);
    }
}