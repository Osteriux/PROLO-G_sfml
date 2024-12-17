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

void GameObject::setSpritePosition(sf::Vector2f position)
{
    animation->setPosition(position);
}

void GameObject::setSpriteScale(sf::Vector2f scale)
{
    animation->setScale(scale);
}

void GameObject::update(float dt)
{
    animation->update(dt);
}

void GameObject::draw(sf::RenderTarget &target)
{
    target.draw(*animation);
}
