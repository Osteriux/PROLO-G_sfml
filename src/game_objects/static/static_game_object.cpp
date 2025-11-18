#include "static_game_object.h"

StaticGameObject::StaticGameObject(std::unique_ptr<MultiTexture> animation, GameManager *gameManager, int x, int y)
    : GameObject(std::move(animation), gameManager, x, y)
{
}