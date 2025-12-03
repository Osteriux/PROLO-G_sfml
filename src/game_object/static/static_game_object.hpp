#pragma once
#include "../game_object.hpp"

class DynamicGameObject;

class StaticGameObject : public GameObject
{
public:
    StaticGameObject(std::unique_ptr<MultiTexture> animation, int x, int y);
    virtual void action(DynamicGameObject *user) = 0;
    ~StaticGameObject() = default;
};
