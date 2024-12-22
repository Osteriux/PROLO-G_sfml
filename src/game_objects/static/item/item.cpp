#include "../../dynamic/joueur/joueur.h"
#include "item.h"

Item::Item(std::string texture_path, Carte* carte, int x, int y)
    : StaticGameObject(std::make_unique<MultiTexture>(texture_path, 1), carte, x, y)
{
}

std::vector<Item::ItemType> Item::getAllItemTypes()
{
    return {ItemType::MINE, ItemType::BATTERIE, ItemType::BOMBE, ItemType::DETECTEUR};
}

std::string Item::itemTypeToString(ItemType type)
{
    switch (type)
    {
    case ItemType::MINE:
        return "MINE";
    case ItemType::BATTERIE:
        return "BATTERIE";
    case ItemType::BOMBE:
        return "BOMBE";
    case ItemType::DETECTEUR:
        return "DETECTEUR";
    default:
        throw std::invalid_argument("Invalid item type");
    }
}

Item::ItemType Item::stringToItemType(std::string type)
{
    if (type == "MINE")
        return ItemType::MINE;
    else if (type == "BATTERIE")
        return ItemType::BATTERIE;
    else if (type == "BOMBE")
        return ItemType::BOMBE;
    else if (type == "DETECTEUR")
        return ItemType::DETECTEUR;
    else
        throw std::invalid_argument("Invalid item type");
}

int Item::itemTypeToId(ItemType type)
{
    switch (type)
    {
    case ItemType::MINE:
        return 0;
    case ItemType::BATTERIE:
        return 1;
    case ItemType::BOMBE:
        return 2;
    case ItemType::DETECTEUR:
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
        return ItemType::BATTERIE;
    case 2:
        return ItemType::BOMBE;
    case 3:
        return ItemType::DETECTEUR;
    default:
        throw std::invalid_argument("Invalid item id");
    }
}
