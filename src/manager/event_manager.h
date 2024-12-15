#pragma once
#include "game_manager.h"

class EventManager
{
private:
    GameManager* gameManager;
    void handleKeyboardPressed(sf::Event::KeyEvent event);
    void handleKeyboardReleased(sf::Event::KeyEvent event);
    void handleMousePressed(sf::Event::MouseButtonEvent event);
public:
    EventManager(GameManager* gameManager);
    void handleEvents(sf::Event event);
    ~EventManager() = default;
};
