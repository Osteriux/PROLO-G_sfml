#include "item.h"

Item::Item(std::string texture_path, Carte* carte, int x, int y)
    : StaticGameObject(std::make_unique<MultiTexture>(texture_path, 1), carte, x, y)
{
}
