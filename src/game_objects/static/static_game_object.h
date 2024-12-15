#pragma once
#include "../game_object.h"

class StaticGameObject : public GameObject
{
public:
    StaticGameObject(std::unique_ptr<MultiTexture> animation, Carte* carte, int x, int y);
    virtual void action(DynamicGameObject* user) = 0;
    ~StaticGameObject() = default;
};
