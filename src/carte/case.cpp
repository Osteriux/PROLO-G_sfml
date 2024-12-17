#include "case.h"
#include "../game_objects/dynamic/dynamic_game_object.h"
#include "../game_objects/static/static_game_object.h"

Case::Case(int x, int y, int room, sf::Vector2f position, std::vector<Direction::Dir> passages, std::map<Direction::Dir, sf::Color> portes)
    : x(x), y(y), room(room), position(position), passages(passages), portes()
{
    for(auto& porte : portes){
        this->portes[porte.first] = std::make_unique<Porte>(porte.second, porte.first);
    }
    this->texture.loadFromFile(texturePath(passages, portes));
    this->setTexture(texture);
    this->entity = std::move(entity);
    this->items = std::move(items);
    this->setPosition(position);
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
    this->entity->setSpritePosition(position);
}

void Case::addItem(std::unique_ptr<StaticGameObject> item)
{
    items.push_back(std::move(item));
    this->entity->setSpritePosition(position);
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

void Case::draw(sf::RenderTarget &target)
{
    // dessin du fond de la case
    target.draw(*this);
    // dessin des portes
    for(auto& porte : portes){ 
        porte.second->draw(target);
    }
    // dessin de l'entité si elle existe
    if (entity)
    {
        entity->draw(target);
    }
    // dessin des items
    for (auto &item : items)
    {
        item->draw(target);
    }
}

std::string Case::texturePath(std::vector<Direction::Dir> passages, std::map<Direction::Dir, sf::Color> portes){
    std::string path = "assets/cases/";
    for(auto& passage : passages){
        path += Direction::directionToString(passage);
        path += "-";
    }
    path += "case";
    for(auto& porte : portes){
        path += "_";
        path += Direction::directionToString(porte.first);
    }
    path += ".png";
    return path;
}
