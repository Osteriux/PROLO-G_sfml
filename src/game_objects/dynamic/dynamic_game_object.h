#pragma once
#include "../game_object.h"
#include "../../carte/direction.h"

class DynamicGameObject : public GameObject
{
public:
    DynamicGameObject(int health, int speed, std::unique_ptr<MultiTexture> animation, Carte* carte, int x, int y);
    ~DynamicGameObject() = default;
protected:
    int health;
    int speed;
    virtual void move(Direction::Dir direction);
};