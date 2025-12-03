#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "../manager/game_event_system.hpp"

class Log : public IEventListener
{
private:
    sf::RectangleShape outline;
    std::vector<sf::Text> messages;
    const int maxMessages;
    sf::Vector2u origin;
    sf::Font font;
    sf::FloatRect rect;
public:
    Log(int maxMessages, sf::Vector2u origin, sf::Vector2u size);
    void init();  // Subscribe to events after GameManager is ready
    void scrollUp();
    void scrollDown();
    void addMessage(std::string message);
    void draw(sf::RenderWindow &window);
    void onEvent(const GameEvent &event) override;
    ~Log();
};
