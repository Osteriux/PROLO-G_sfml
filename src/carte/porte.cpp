#include "porte.h"

Porte::Porte(sf::Color color, Direction::Dir dir, sf::Vector2f position)
     : ouverte(false), dir(dir), color(color), bgOffset(0, 0), texture(texturePath(dir), 2)
{
    bg = createColorRect(dir, position);
    bg.setFillColor(color);
    setPosition(position);
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
    sf::Vector2f scale = bg.getScale();
    bg.setPosition(position + sf::Vector2f(bgOffset.x * scale.x, bgOffset.y * scale.y));
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

sf::RectangleShape Porte::createColorRect(Direction::Dir dir, sf::Vector2f position)
{
    sf::Vector2f size;
    switch (dir)
    {
        case Direction::Dir::UP:
        case Direction::Dir::DOWN:
            size = sf::Vector2f(8, 4);
            break;
        case Direction::Dir::LEFT:
        case Direction::Dir::RIGHT:
            size = sf::Vector2f(4, 8);
            break;
        default:
            throw std::invalid_argument("Invalid direction");
    }
    sf::RectangleShape r(size);
    sf::Vector2f offset;
    switch (dir)
    {
        case Direction::Dir::UP:
            offset = sf::Vector2f(12, 0);
            break;
        case Direction::Dir::DOWN:
            offset = sf::Vector2f(12, 28);
            break;
        case Direction::Dir::LEFT:
            offset = sf::Vector2f(0, 12);
            break;
        case Direction::Dir::RIGHT:
            offset = sf::Vector2f(28, 12);
            break;
        default:
            throw std::invalid_argument("Invalid direction");
    }
    bgOffset = offset;
    return r;
}
