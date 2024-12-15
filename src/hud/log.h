#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Log
{
private:
    std::vector<sf::Text> messages;
    const int maxMessages;
    sf::Vector2f origin;
    sf::Font font;
    sf::FloatRect rect;
public:
    Log(int maxMessages, sf::Vector2f origin, sf::Vector2f size);
    void scrollUp();
    void scrollDown();
    void addMessage(std::string message);
    void draw(sf::RenderWindow &window);
    ~Log() = default;
};
