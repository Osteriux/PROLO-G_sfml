#pragma once
#include "../static_game_object.h"

class Item : public StaticGameObject
{
public:
    enum class ItemType
    {
        MINE,
        BATTERIE,
        BOMBE,
        RADAR,
        DETECTEUR
    };
    Item(std::string texture_path, Carte* carte, int x, int y);
    virtual std::string getDescription() = 0;
    ~Item() = default;
};