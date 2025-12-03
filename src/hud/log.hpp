#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Log
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
    void scrollUp();
    void scrollDown();
    void addMessage(std::string message);
    void draw(sf::RenderWindow &window);
    ~Log() = default;
};
