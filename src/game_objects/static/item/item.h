#pragma once
#include "../static_game_object.h"

class GameManager;

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

    Item(std::string texture_path, GameManager* gameManager, int x, int y);
    void ramasser(Joueur* user);
    ~Item() = default;
protected:
    ItemType type;
};