#include "game_object.h"

GameObject::GameObject(std::unique_ptr<MultiTexture> animation, Carte* carte, int x, int y)
    : carte(carte)
{
    this->animation = std::move(animation);
    currCase = carte->getCase(x, y);
}

Case* GameObject::getCase()
{
    return currCase;
}

void GameObject::update(float dt)
{
    animation->update(dt);
}

void GameObject::draw(sf::RenderWindow &window)
{
    window.draw(*animation);
}