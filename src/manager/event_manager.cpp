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
    case sf::Keyboard::Up:
        std::cout << "Carte up" << std::endl;
        gameManager->getCarte()->move(sf::Vector2f(0, Case::SIZE));
        break;
    case sf::Keyboard::Down:
        std::cout << "Carte down" << std::endl;
        gameManager->getCarte()->move(sf::Vector2f(0, -Case::SIZE));
        break;
    case sf::Keyboard::Left:
        std::cout << "Carte left" << std::endl;
        gameManager->getCarte()->move(sf::Vector2f(Case::SIZE, 0));
        break;
    case sf::Keyboard::Right:
        std::cout << "Carte right" << std::endl;
        gameManager->getCarte()->move(sf::Vector2f(-Case::SIZE, 0));
        break;
    case sf::Keyboard::R:
        std::cout << "Carte reset" << std::endl;
        gameManager->getCarte()->reset();
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
    gameManager->getHUD().onClic(sf::Vector2f(event.x, event.y));
    switch (event.button)
    {
    default:
        break;
    }
}

