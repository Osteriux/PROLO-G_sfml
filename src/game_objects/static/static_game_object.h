#pragma once
#include "../game_object.h"
#include "../dynamic/dynamic_game_object.h"

class StaticGameObject : public GameObject
{
public:
    StaticGameObject(std::unique_ptr<MultiTexture> animation, GameManager* gameManager, int x, int y);
    virtual void action(DynamicGameObject* user) = 0;
    ~StaticGameObject() = default;
};
