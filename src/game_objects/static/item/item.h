#pragma once
#include "../static_game_object.h"

class GameManager;

class Player;

class Item : public StaticGameObject
{
public:
    enum class ItemType
    {
        MINE,
        BATTERY,
        BOMB,
        DETECTOR
    };
    static const ItemType MINE = ItemType::MINE;
    static const ItemType BATTERY = ItemType::BATTERY;
    static const ItemType BOMB = ItemType::BOMB;
    static const ItemType DETECTOR = ItemType::DETECTOR;
    static std::string itemTypeToString(ItemType type);
    static ItemType stringToItemType(std::string type);
    static int itemTypeToId(ItemType type);
    static ItemType idToItemType(int id);
    static std::vector<ItemType> getAllItemTypes();

    Item(std::unique_ptr<MultiTexture> tex, int x, int y);
    void pickup(Player* user);
    ~Item() = default;
protected:
    ItemType type;
    static std::string texturePath(ItemType type);
};