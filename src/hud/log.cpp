#include "log.h"

Log::Log(int maxMessages, sf::Vector2f origin, sf::Vector2f size)
    : maxMessages(maxMessages), origin(origin), rect(sf::FloatRect(origin.x, origin.y, size.x, size.y))
{
    if(!font.loadFromFile("assets/fonts/arial.ttf")){
        std::cerr << "Error loading assets/fonts/arial.ttf" << std::endl;
    }
}

void Log::scrollUp()
{
    for (sf::Text &message : messages)
    {
        message.move(0, -20);
    }
}

void Log::scrollDown()
{
    for (sf::Text &message : messages)
    {
        message.move(0, 20);
    }
}

void Log::addMessage(std::string message)
{
    if (messages.size() == maxMessages)
    {
        messages.erase(messages.begin());
    }
    messages.push_back(sf::Text(message, font));
}

void Log::draw(sf::RenderWindow &window)
{
    sf::View originalView = window.getView();
    sf::View view(sf::FloatRect(rect.left, rect.top, rect.width, rect.height));
    window.setView(view);
    for (sf::Text &message : messages)
    {
        window.draw(message);
    }
    window.setView(originalView);
}