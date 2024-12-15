#include "static_game_object.h"

StaticGameObject::StaticGameObject(std::unique_ptr<MultiTexture> animation, Carte* carte, int x, int y)
    : GameObject(std::move(animation), carte, x, y)
{
}