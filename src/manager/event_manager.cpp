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
    switch (event.code)
    {
    case sf::Keyboard::PageUp:
    case sf::Keyboard::Add:
        std::cout << "Zoom in" << std::endl;
        gameManager->getCarte()->scaleUp();
        break;
    case sf::Keyboard::PageDown:
    case sf::Keyboard::Subtract:
        std::cout << "Zoom out" << std::endl;
        gameManager->getCarte()->scaleDown();
        break;
    default:
        break;
    }
}

void EventManager::handleKeyboardReleased(sf::Event::KeyEvent event)
{
    switch (event.code)
    {
    default:
        break;
    }
}

void EventManager::handleMousePressed(sf::Event::MouseButtonEvent event)
{
    switch (event.button)
    {
    default:
        break;
    }
}

