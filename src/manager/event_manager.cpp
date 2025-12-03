#include "event_manager.hpp"
#include "game_manager.hpp"
#include "../map/case.hpp"

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
        std::cout << "Zoom in" << std::endl;
        GameManager::getInstance().getMap()->scaleUp();
        break;
    case sf::Keyboard::PageDown:
    case sf::Keyboard::Subtract:
        std::cout << "Zoom out" << std::endl;
        GameManager::getInstance().getMap()->scaleDown();
        break;
    case sf::Keyboard::Up:
        std::cout << "Map up" << std::endl;
        GameManager::getInstance().getMap()->move(sf::Vector2f(0, -Case::SIZE));
        break;
    case sf::Keyboard::Down:
        std::cout << "Map down" << std::endl;
        GameManager::getInstance().getMap()->move(sf::Vector2f(0, Case::SIZE));
        break;
    case sf::Keyboard::Left:
        std::cout << "Map left" << std::endl;
        GameManager::getInstance().getMap()->move(sf::Vector2f(-Case::SIZE, 0));
        break;
    case sf::Keyboard::Right:
        std::cout << "Map right" << std::endl;
        GameManager::getInstance().getMap()->move(sf::Vector2f(Case::SIZE, 0));
        break;
    case sf::Keyboard::R:
        std::cout << "Map reset" << std::endl;
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
    GameManager::getInstance().getHUD().onClic(sf::Vector2f(event.x, event.y));
    switch (event.button)
    {
    default:
        break;
    }
}
