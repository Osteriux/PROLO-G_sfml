#include "button_text.h"

ButtonText::ButtonText(sf::Vector2f position, sf::Vector2f size, std::string text, sf::Color backgroundColor, sf::Color textColor)
    : ButtonBase(position, size, backgroundColor)
{
    if (!font.loadFromFile("assets/fonts/arial.ttf"))
    {
        std::cerr << "Error loading font : assets/fonts/arial.ttf" << std::endl;
    }
    this->text.setFont(font);
    this->text.setString(text);
    this->text.setCharacterSize(24);
    this->text.setFillColor(textColor);
    this->text.setPosition(position.x + 10, position.y + 10);
}

void ButtonText::draw(sf::RenderWindow &window)
{
    ButtonBase::draw(window);
    window.draw(text);
}