#include "../../dynamic/player/player.h"
#include "../../../manager/game_manager.h"
#include "item.h"

Item::Item(std::unique_ptr<MultiTexture> tex, int x, int y)
    : StaticGameObject(std::move(tex), x, y)
{
}

void Item::pickup(Player* user)
{
    user->getInventory().addItem(type);
}

std::vector<Item::ItemType> Item::getAllItemTypes()
{
    return {ItemType::MINE, ItemType::BATTERY, ItemType::BOMB, ItemType::DETECTOR};
}

std::string Item::itemTypeToString(ItemType type)
{
    switch (type)
    {
    case ItemType::MINE:
        return "MINE";
    case ItemType::BATTERY:
        return "BATTERY";
    case ItemType::BOMB:
        return "BOMB";
    case ItemType::DETECTOR:
        return "DETECTOR";
    default:
        throw std::invalid_argument("Invalid item type");
    }
}

Item::ItemType Item::stringToItemType(std::string type)
{
    if (type == "MINE")
        return ItemType::MINE;
    else if (type == "BATTERY")
        return ItemType::BATTERY;
    else if (type == "BOMB")
        return ItemType::BOMB;
    else if (type == "DETECTOR")
        return ItemType::DETECTOR;
    else
        throw std::invalid_argument("Invalid item type");
}

int Item::itemTypeToId(ItemType type)
{
    switch (type)
    {
    case ItemType::MINE:
        return 0;
    case ItemType::BATTERY:
        return 1;
    case ItemType::BOMB:
        return 2;
    case ItemType::DETECTOR:
        return 3;
    default:
        throw std::invalid_argument("Invalid item id");
    }
}

Item::ItemType Item::idToItemType(int id)
{
    switch (id)
    {
    case 0:
        return ItemType::MINE;
    case 1:
        return ItemType::BATTERY;
    case 2:
        return ItemType::BOMB;
    case 3:
        return ItemType::DETECTOR;
    default:
        throw std::invalid_argument("Invalid item id");
    }
}

std::string Item::texturePath(ItemType type)
{
    return "assets/static/" + itemTypeToString(type) + ".png";
}
