#include "static_game_object.h"

StaticGameObject::StaticGameObject(std::unique_ptr<MultiTexture> animation, int x, int y)
    : GameObject(std::move(animation), x, y)
{
}