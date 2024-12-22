#include "../manager/game_manager.h"
#include "../carte/carte.h"
#include "../carte/case.h"
#include "game_object.h"

GameObject::GameObject(std::unique_ptr<MultiTexture> animation, GameManager* gameManager, int x, int y)
    : gameManager(gameManager)
{
    this->animation = std::move(animation);
}

Case* GameObject::getCase()
{
    return currCase;
}

void GameObject::setCase(Case* newCase)
{
    currCase = newCase;
}

void GameObject::setSpritePosition(sf::Vector2f position)
{
    if(animation == nullptr)
    {
        throw std::runtime_error("GameObject::setSpritePosition: animation is nullptr");
    }
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
