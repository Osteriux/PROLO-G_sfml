#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "../animations/multi_texture.h"

class GameManager;
class Case;

class GameObject
{
protected:
    std::unique_ptr<MultiTexture> animation;
    Case *currCase;

public:
    GameObject(std::unique_ptr<MultiTexture> animation, int x, int y);
    Case *getCase();
    void setCase(Case *newCase);
    void setSpritePosition(sf::Vector2f position);
    void setSpriteScale(sf::Vector2f scale);
    virtual std::string getDescription() const = 0;
    virtual void update(float dt);
    virtual void draw(sf::RenderTarget &target);
    ~GameObject() = default;
};
