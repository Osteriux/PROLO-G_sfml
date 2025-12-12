#include "../manager/game_manager.hpp"
#include "../map/map.hpp"
#include "../map/case.hpp"
#include "game_object.hpp"
#include "../utils/logger/logger.hpp"

GameObject::GameObject(std::unique_ptr<MultiTexture> animation, int x, int y)
    : currCase(nullptr)
{
    this->animation = std::move(animation);
}

Case *GameObject::getCase()
{
    return currCase;
}

void GameObject::setCase(Case *newCase)
{
    currCase = newCase;
}

void GameObject::setSpritePosition(sf::Vector2f position)
{
    if (animation == nullptr)
    {
        Logger::log("GameObject::setSpritePosition: animation is nullptr", Logger::ERROR);
        throw std::runtime_error("GameObject::setSpritePosition: animation is nullptr");
    }
    animation->setPosition(position);
}

void GameObject::setSpriteScale(sf::Vector2f scale)
{
    if (!animation)
    {
        Logger::log("GameObject::setSpritePosition: animation is nullptr", Logger::ERROR);
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
