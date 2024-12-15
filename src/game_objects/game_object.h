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
    virtual void update(float dt);
    virtual void draw(sf::RenderWindow &window);
    ~GameObject() = default;
};
