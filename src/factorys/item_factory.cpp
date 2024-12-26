#include "item_factory.h"

std::unique_ptr<Item> ItemFactory::createItem(int x, int y, int type, GameManager* gameManager)
{
    std::cout << "creatind item " << type << " at : " << x << "," << y << std::endl;
    Item::ItemType itemType = Item::idToItemType(type);
    switch (itemType)
    {
    case Item::ItemType::MINE:
        return std::make_unique<Mine>(x, y, gameManager);
    case Item::ItemType::BATTERIE:
        return std::make_unique<Batterie>(x, y, gameManager);
    case Item::ItemType::BOMBE:
        return std::make_unique<Bombe>(x, y, gameManager);
    case Item::ItemType::DETECTEUR:
        return std::make_unique<Detecteur>(x, y, gameManager);
    default:
        throw std::invalid_argument("Invalid item type");
    }
}