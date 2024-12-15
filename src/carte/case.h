#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class DynamicGameObject;
class StaticGameObject;

class Case : public sf::Sprite{
private:
    sf::Texture texture;
    std::unique_ptr<DynamicGameObject> entity;
    std::vector<std::unique_ptr<StaticGameObject>> items;
    int x, y;
    int room;
public:
    Case(int x, int y, int room);
    int getRoom();
    int getX();
    int getY();
    void transferEntity(Case* nextCase);
    void setEntity(std::unique_ptr<DynamicGameObject> entity);
    void addItem(std::unique_ptr<StaticGameObject> item);
    void removeItem(int index);
    void update(float dt);
    void draw(sf::RenderWindow &window);
    ~Case() = default;
};