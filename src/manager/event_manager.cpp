#include "event_manager.h"

EventManager::EventManager(GameManager *gameManager)
    : gameManager(gameManager)
{
}


void EventManager::handleEvents(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        handleKeyboardPressed(event.key);
        break;
    case sf::Event::KeyReleased:
        handleKeyboardReleased(event.key);
        break;
    case sf::Event::MouseButtonPressed:
        handleMousePressed(event.mouseButton);
        break;
    default:
        break;
    }
}

void EventManager::handleKeyboardPressed(sf::Event::KeyEvent event)
{
}

void EventManager::handleKeyboardReleased(sf::Event::KeyEvent event)
{
}

void EventManager::handleMousePressed(sf::Event::MouseButtonEvent event)
{
}

