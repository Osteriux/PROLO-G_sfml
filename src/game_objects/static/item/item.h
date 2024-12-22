#pragma once
#include "../static_game_object.h"

class Joueur;

class Item : public StaticGameObject
{
public:
    enum class ItemType
    {
        MINE,
        BATTERIE,
        BOMBE,
        DETECTEUR
    };
    static std::string itemTypeToString(ItemType type);
    static ItemType stringToItemType(std::string type);
    static int itemTypeToId(ItemType type);
    static ItemType idToItemType(int id);
    static std::vector<ItemType> getAllItemTypes();

    Item(std::string texture_path, Carte* carte, int x, int y);
    virtual void ramasser(Joueur* user) = 0;
    ~Item() = default;
};