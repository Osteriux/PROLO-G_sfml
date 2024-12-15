#pragma once
#include "../game_object.h"

class DynamicGameObject : public GameObject
{
public:
    DynamicGameObject(int health, int speed, std::unique_ptr<MultiTexture> animation, Carte* carte, int x, int y);
    enum class Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    ~DynamicGameObject() = default;
protected:
    int health;
    int speed;
    virtual void move(Direction direction);
};