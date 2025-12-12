#include "event_manager.hpp"
#include "game_manager.hpp"
#include "../map/case.hpp"
#include "../utils/logger/logger.hpp"

EventManager::EventManager()
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
        Logger::log("Zoom in", Logger::INFO);
        GameManager::getInstance().getMap()->scaleUp();
        break;
    case sf::Keyboard::PageDown:
    case sf::Keyboard::Subtract:
        Logger::log("Zoom out", Logger::INFO);
        GameManager::getInstance().getMap()->scaleDown();
        break;
    case sf::Keyboard::Up:
        Logger::log("Map up", Logger::INFO);
        GameManager::getInstance().getMap()->move(sf::Vector2f(0, -Case::SIZE));
        break;
    case sf::Keyboard::Down:
        Logger::log("Map down", Logger::INFO);
        GameManager::getInstance().getMap()->move(sf::Vector2f(0, Case::SIZE));
        break;
    case sf::Keyboard::Left:
        Logger::log("Map left", Logger::INFO);
        GameManager::getInstance().getMap()->move(sf::Vector2f(-Case::SIZE, 0));
        break;
    case sf::Keyboard::Right:
        Logger::log("Map right", Logger::INFO);
        GameManager::getInstance().getMap()->move(sf::Vector2f(Case::SIZE, 0));
        break;
    case sf::Keyboard::R:
        Logger::log("Map reset", Logger::INFO);
        GameManager::getInstance().getMap()->reset();
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
    // Convert window coordinates to design resolution coordinates
    // accounting for scaling and letterboxing
    sf::Vector2f designCoords = GameManager::getInstance().getViewportManager().windowToDesignCoordinates(
        sf::Vector2f(static_cast<float>(event.x), static_cast<float>(event.y))
    );
    
    GameManager::getInstance().getHUD().onClic(designCoords);
    switch (event.button)
    {
    default:
        break;
    }
}
