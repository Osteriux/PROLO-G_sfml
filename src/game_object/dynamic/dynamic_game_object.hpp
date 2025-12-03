#pragma once
#include "../game_object.hpp"
#include "../../map/direction.hpp"

class DynamicGameObject : public GameObject
{
protected:
    int health;
    int speed;
    virtual void move(Direction::Dir direction);
public:
    DynamicGameObject(int health, int speed, std::unique_ptr<MultiTexture> animation, int x, int y);
    int getHealth();
    ~DynamicGameObject() = default;
};