#include "porte.h"

Porte::Porte(sf::Color color, Direction::Dir dir, sf::Vector2f position)
     : ouverte(false), dir(dir), color(color)
{
    texture = MultiTexture(texturePath(dir), 2);
    bg = sf::RectangleShape(texture.getSize());
    bg.setFillColor(color);
    bg.setPosition(position);
    texture.setPosition(position);
}

bool Porte::estOuverte()
{
    return ouverte;
}

void Porte::ouvrir()
{
    texture.setColumn(1);
    ouverte = true;
}

void Porte::fermer()
{
    texture.setColumn(0);
    ouverte = false;
}

sf::Color Porte::getColor()
{
    return color;
}

void Porte::setPosition(sf::Vector2f position)
{
    bg.setPosition(position);
    texture.setPosition(position);
}

void Porte::setScale(sf::Vector2f scale)
{
    bg.setScale(scale);
    texture.setScale(scale);
}

void Porte::draw(sf::RenderTarget &target)
{
    target.draw(bg);
    target.draw(texture);
}

std::string Porte::texturePath(Direction::Dir dir)
{
    std::stringstream ss;
    ss << "assets/portes/" << Direction::directionToString(dir) << ".png";
    return ss.str();
}
