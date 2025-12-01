#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class EventManager
{
private:
    void handleKeyboardPressed(sf::Event::KeyEvent event);
    void handleKeyboardReleased(sf::Event::KeyEvent event);
    void handleMousePressed(sf::Event::MouseButtonEvent event);

public:
    EventManager();
    void handleEvents(sf::Event event);
    ~EventManager() = default;
};
