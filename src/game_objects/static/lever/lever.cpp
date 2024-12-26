#include "lever.h"

Lever::Lever(sf::Color color, GameManager* gameManager, int x, int y, int doorId, int nb)
    : StaticGameObject(createRect(color, nb), gameManager, x, y), activated(false), doorId(doorId)
{
}

void Lever::action(DynamicGameObject* user)
{
    activated = !activated;
    if (activated)
    {
        std::cout << "Door " << doorId << " opened" << std::endl;
    }
    else
    {
        std::cout << "Door " << doorId << " closed" << std::endl;
    }
}

std::string Lever::getDescription()
{
    return "Levier";
}

std::unique_ptr<MultiTexture> Lever::createRect(sf::Color color, int nb)
{
    if(nb > 20){
        throw std::invalid_argument("trop de levier sur le même case : must be less than 20");
    }
    sf::Vector2f pos(7, 7);
    if(nb > 10){
        pos.x = 21;
    }
    if((nb / 5) % 2 == 1){
        pos.x += 3;
    }
    pos.y += 3 * (nb % 5);
    std::cout << "Creating lever " << nb << " at : " << pos.x << " " << pos.y << std::endl;
    return std::make_unique<MultiTexture>(color, 3, 3, pos);
}