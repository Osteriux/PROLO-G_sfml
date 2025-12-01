#include "case.h"
#include "../game_objects/dynamic/dynamic_game_object.h"
#include "../game_objects/static/static_game_object.h"

Case::Case(int x, int y, int room, sf::Vector2f position, std::vector<Direction::Dir> passages, std::map<Direction::Dir, sf::Color> doors)
    : x(x), y(y), room(room), position(position), passages(passages)
{
    for(auto& door : doors){
        this->doors[door.first] = std::make_unique<Door>(door.second, door.first, position);
    }
    this->texture.loadFromFile(texturePath(passages, doors));
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

std::map<Direction::Dir, bool> Case::getAdjacent()
{
    std::map<Direction::Dir, bool> adjacent;
    for(auto direction : Direction::DIRECTIONS){
        if(std::find(passages.begin(), passages.end(), direction) != passages.end()){
            adjacent[direction] = true;
        } else if (doors.find(direction) != doors.end())
        {
            adjacent[direction] = doors[direction]->estOuverte();
        }
        else {
            adjacent[direction] = false;
        }
    }
    return adjacent;
}

void Case::setPosition(sf::Vector2f position)
{
    this->position = position;
    sf::Sprite::setPosition(position);
    for(auto& door : doors){
        door.second->setPosition(position);
    }
    for(auto& item : items){
        item->setSpritePosition(position);
    }
    if(entity){
        entity->setSpritePosition(position);
    }
}

void Case::setScale(sf::Vector2f scale)
{
    sf::Sprite::setScale(scale);
    for(auto& door : doors){
        door.second->setScale(scale);
    }
    for(auto& item : items){
        item->setSpriteScale(scale);
    }
    if(entity){
        entity->setSpriteScale(scale);
    }
}

void Case::transferEntity(Case *nextCase)
{
    nextCase->setEntity(std::move(entity));
    entity = nullptr;
}

void Case::setEntity(std::unique_ptr<DynamicGameObject> entity)
{
    entity->setSpritePosition(position);
    entity->setCase(this);
    this->entity = std::move(entity);
}

void Case::addItem(std::unique_ptr<StaticGameObject> item)
{
    item->setSpriteScale(this->getScale());
    item->setSpritePosition(position);
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

void Case::draw(sf::RenderTarget &target)
{
    // dessin du fond de la case
    target.draw(*this);
    // dessin des doors
    for(auto& door : doors){ 
        door.second->draw(target);
    }
    // dessin des items
    for (auto &item : items)
    {
        item->draw(target);
    }
    // dessin de l'entité si elle existe
    if (entity)
    {
        entity->draw(target);
    }
}

std::string Case::texturePath(std::vector<Direction::Dir> passages, std::map<Direction::Dir, sf::Color> doors){
    std::string path = "assets/cases/";
    for(auto& door : doors){
        path += Direction::directionToString(door.first);
        path += "-";
    }
    path += "case";
    for(auto& passage : passages){
        path += "_";
        path += Direction::directionToString(passage);
    }
    path += ".png";
    return path;
}
