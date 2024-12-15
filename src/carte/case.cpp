#include "case.h"
#include "../game_objects/dynamic/dynamic_game_object.h"
#include "../game_objects/static/static_game_object.h"

Case::Case(int x, int y, int room)
    : x(x), y(y), room(room)
{
    sf::RectangleShape rec(sf::Vector2f(32, 32));
    rec.setFillColor(sf::Color::Transparent);
    rec.setOutlineColor(sf::Color::White);
    this->texture = *rec.getTexture();
    this->setTexture(texture);
    this->entity = std::move(entity);
    this->items = std::move(items);
}

int Case::getRoom()
{
    return room;
}

int Case::getX()
{
    return x;
}

int Case::getY()
{
    return y;
}

void Case::transferEntity(Case *nextCase)
{
    nextCase->setEntity(std::move(entity));
    entity = nullptr;
}

void Case::setEntity(std::unique_ptr<DynamicGameObject> entity)
{
    this->entity = std::move(entity);
}

void Case::addItem(std::unique_ptr<StaticGameObject> item)
{
    items.push_back(std::move(item));
}

void Case::removeItem(int index)
{
    items.erase(items.begin() + index);
}

void Case::update(float dt)
{
    if (entity)
    {
        entity->update(dt);
    }
    for (auto &item : items)
    {
        item->update(dt);
    }
}

void Case::draw(sf::RenderWindow &window)
{
    window.draw(*this);
    if (entity)
    {
        entity->draw(window);
    }
    for (auto &item : items)
    {
        item->draw(window);
    }
}
