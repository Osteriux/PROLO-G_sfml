#include "porte.h"

Porte::Porte(sf::Color color, Direction::Dir dir)
     : ouverte(false), dir(dir), color(color)
{
    std::stringstream ss;
    ss << "assets/porte_" << Direction::directionToString(dir) << ".png";
    texture = MultiTexture(ss.str(), 2);
    bg = sf::RectangleShape(texture.getSize());
    bg.setFillColor(color);
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

void Porte::draw(sf::RenderWindow &window)
{
    window.draw(texture);
}