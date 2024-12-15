#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "case.h"

class Carte
{
private:
    sf::Vector2u regionSize;
    sf::Vector2f scale;
    sf::RectangleShape outline;
    std::vector<std::vector<std::unique_ptr<Case>>> cases;
    sf::Vector2f origin;
    std::vector<int> seenRooms;
    std::vector<int> openedDoors;
    int nbLines, nbColumns;
    float offset;
public:
    Carte(int nbLines, int nbColumns, sf::Vector2f origin, float offset, sf::Vector2u regionSize);
    Case* getCase(int x, int y);
    void addSeenRoom(int room);
    void addOpenedDoor(int doorId);
    void removeOpenedDoor(int doorId);
    void scaleUp();
    void scaleDown();
    void update(float dt);
    void draw(sf::RenderWindow &window);
    ~Carte() = default;
};
