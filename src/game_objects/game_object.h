#pragma once
#include <iostream>
#include <memory>
#include "../animations/multi_texture.h"
#include "../carte/case.h"
#include "../carte/carte.h"

class GameObject
{
protected:
    std::unique_ptr<MultiTexture> animation;
    Carte* carte;
    Case* currCase;
public:
    GameObject(std::unique_ptr<MultiTexture> animation, Carte* carte, int x, int y);
    Case* getCase();
    void setSpritePosition(sf::Vector2f position);
    void setSpriteScale(sf::Vector2f scale);
    virtual void update(float dt);
    virtual void draw(sf::RenderTarget &target);
    ~GameObject() = default;
};
