#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <map>
#include <string>
#include "direction.h"
#include "porte.h"

class DynamicGameObject;
class StaticGameObject;

class Case : public sf::Sprite{
private:
    sf::Texture texture;
    std::unique_ptr<DynamicGameObject> entity;
    std::vector<std::unique_ptr<StaticGameObject>> items;
    std::vector<Direction::Dir> passages;
    std::map<Direction::Dir, std::unique_ptr<Porte>> portes;
    sf::Vector2f position;
    int x, y;
    int room;
    std::string texturePath(std::vector<Direction::Dir> passages, std::map<Direction::Dir, sf::Color> portes);
public:
    static const int SIZE = 32;
    Case(int x, int y, int room, sf::Vector2f position, std::vector<Direction::Dir> passages, std::map<Direction::Dir, sf::Color> portes);
    int getRoom();
    int getX();
    int getY();
    std::map<Direction::Dir, bool> getAdjacent();
    void setPosition(sf::Vector2f position);
    void setScale(sf::Vector2f scale);
    void transferEntity(Case* nextCase);
    void setEntity(std::unique_ptr<DynamicGameObject> entity);
    void addItem(std::unique_ptr<StaticGameObject> item);
    void removeItem(int index);
    void update(float dt);
    void draw(sf::RenderTarget &target);
    ~Case() = default;
};