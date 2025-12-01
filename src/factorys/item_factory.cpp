#include "item_factory.h"

std::unique_ptr<Item> ItemFactory::createItem(int type, int x, int y)
{
    std::cout << "Creating item " << type << " at : " << x << "," << y << std::endl;
    Item::ItemType itemType = Item::idToItemType(type);
    switch (itemType)
    {
    case Item::ItemType::MINE:
        return std::make_unique<Mine>(x, y);
    case Item::ItemType::BATTERY:
        return std::make_unique<Battery>(x, y);
    case Item::ItemType::BOMB:
        return std::make_unique<Bomb>(x, y);
    case Item::ItemType::DETECTOR:
        return std::make_unique<Detector>(x, y);
    default:
        throw std::invalid_argument("Invalid item type");
    }
}

std::unique_ptr<Lever> ItemFactory::createLever(sf::Color color, int x, int y, int doorId, int nb)
{
    return std::make_unique<Lever>(color, x, y, doorId, nb);
}