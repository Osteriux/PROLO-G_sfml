#include "case.hpp"
#include "../game_object/dynamic/dynamic_game_object.hpp"
#include "../game_object/static/pickup/pickup.hpp"
#include "../game_object/static/interactible/interactible.hpp"

Case::Case(int x, int y, int room, sf::Vector2f position, std::vector<Direction::Dir> passages, std::map<Direction::Dir, std::tuple<int, sf::Color>> doors)
    : x(x), y(y), room(room), position(position), passages(passages)
{
    for (auto &door : doors)
    {
        this->doors[door.first] = std::make_unique<Door>(std::get<1>(door.second), std::get<0>(door.second), door.first, position);
    }
    this->texture.loadFromFile(texturePath(passages, doors));
    this->setTexture(texture);
    this->entity = std::move(entity);
    this->pickups = std::move(pickups);
    this->interactibles = std::move(interactibles);
    this->setPosition(position);
}

void Case::init()
{
    for (auto &door : doors)
    {
        door.second->init();
    }
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
    for (auto direction : Direction::DIRECTIONS)
    {
        if (std::find(passages.begin(), passages.end(), direction) != passages.end())
        {
            adjacent[direction] = true;
        }
        else if (doors.find(direction) != doors.end())
        {
            adjacent[direction] = doors[direction]->estOuverte();
        }
        else
        {
            adjacent[direction] = false;
        }
    }
    return adjacent;
}

void Case::setPosition(sf::Vector2f position)
{
    this->position = position;
    sf::Sprite::setPosition(position);
    for (auto &door : doors)
    {
        door.second->setPosition(position);
    }
    for (auto &pickup : pickups)
    {
        pickup->setSpritePosition(position);
    }
    for (auto &interactible : interactibles)
    {
        interactible->setSpritePosition(position);
    }
    if (entity)
    {
        entity->setSpritePosition(position);
    }
}

void Case::setScale(sf::Vector2f scale)
{
    sf::Sprite::setScale(scale);
    for (auto &door : doors)
    {
        door.second->setScale(scale);
    }
    for (auto &pickup : pickups)
    {
        pickup->setSpriteScale(scale);
    }
    for (auto &interactible : interactibles)
    {
        interactible->setSpriteScale(scale);
    }
    if (entity)
    {
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

void Case::addPickup(std::unique_ptr<Pickup> pickup)
{
    pickup->setCase(this);
    pickup->setSpriteScale(this->getScale());
    pickup->setSpritePosition(position);
    pickups.push_back(std::move(pickup));
}

void Case::removePickup(int index)
{
    pickups.erase(pickups.begin() + index);
}

const std::vector<std::unique_ptr<Pickup>> &Case::getPickups() const
{
    return pickups;
}

void Case::addInteractible(std::unique_ptr<Interactible> interactible)
{
    interactible->setCase(this);
    interactible->setSpriteScale(this->getScale());
    interactible->setSpritePosition(position);
    interactibles.push_back(std::move(interactible));
}

void Case::removeInteractible(int index)
{
    interactibles.erase(interactibles.begin() + index);
}

const std::vector<std::unique_ptr<Interactible>> &Case::getInteractibles() const
{
    return interactibles;
}

void Case::update(float dt)
{
    if (entity)
    {
        entity->update(dt);
    }
    for (auto &pickup : pickups)
    {
        pickup->update(dt);
    }
}

void Case::draw(sf::RenderTarget &target)
{
    // dessin du fond de la case
    target.draw(*this);
    // dessin des doors
    for (auto &door : doors)
    {
        door.second->draw(target);
    }
    // dessin des pickups
    for (auto &pickup : pickups)
    {
        pickup->draw(target);
    }
    // dessin des interactibles
    for (auto &interactible : interactibles)
    {
        interactible->draw(target);
    }
    // dessin de l'entité si elle existe
    if (entity)
    {
        entity->draw(target);
    }
}

std::string Case::texturePath(std::vector<Direction::Dir> passages, std::map<Direction::Dir, std::tuple<int, sf::Color>> doors)
{
    std::string path = "assets/case/";
    for (auto &door : doors)
    {
        path += Direction::directionToString(door.first);
        path += "-";
    }
    path += "case";
    for (auto &passage : passages)
    {
        path += "_";
        path += Direction::directionToString(passage);
    }
    path += ".png";
    return path;
}
