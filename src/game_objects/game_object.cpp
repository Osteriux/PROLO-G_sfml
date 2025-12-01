#include "../manager/game_manager.h"
#include "../map/map.h"
#include "../map/case.h"
#include "game_object.h"

GameObject::GameObject(std::unique_ptr<MultiTexture> animation, int x, int y)
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
    if(!animation)
    {
        std::cerr << "GameObject::setSpritePosition: animation is nullptr" << std::endl;
    }
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
