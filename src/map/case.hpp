#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include "direction.hpp"
#include "door.hpp"

class DynamicGameObject;
class Pickup;
class Interactible;

class Case : public sf::Sprite
{
private:
    sf::Texture texture;
    std::unique_ptr<DynamicGameObject> entity;
    std::vector<std::unique_ptr<Pickup>> pickups;
    std::vector<std::unique_ptr<Interactible>> interactibles;
    std::vector<Direction::Dir> passages;
    std::map<Direction::Dir, std::unique_ptr<Door>> doors;
    sf::Vector2f position;
    int x, y;
    int room;
    std::string texturePath(std::vector<Direction::Dir> passages, std::map<Direction::Dir, std::tuple<int, sf::Color>> doors);

public:
    static const int SIZE = 32;
    Case(int x, int y, int room, sf::Vector2f position, std::vector<Direction::Dir> passages, std::map<Direction::Dir, std::tuple<int, sf::Color>> doors);
    void init();
    int getRoom();
    int getX();
    int getY();
    std::map<Direction::Dir, bool> getAdjacent();
    void setPosition(sf::Vector2f position);
    void setScale(sf::Vector2f scale);
    void transferEntity(Case *nextCase);
    void setEntity(std::unique_ptr<DynamicGameObject> entity);
    void addPickup(std::unique_ptr<Pickup> pickup);
    void removePickup(int index);
    const std::vector<std::unique_ptr<Pickup>> &getPickups() const;
    void addInteractible(std::unique_ptr<Interactible> interactible);
    void removeInteractible(int index);
    const std::vector<std::unique_ptr<Interactible>> &getInteractibles() const;
    void update(float dt);
    void draw(sf::RenderTarget &target);
    ~Case() = default;
};