#pragma once
#include <SFML/Graphics.hpp>
#include <tuple>
#include "case.h"

class Carte
{
private:
    int nbLines, nbColumns;
    std::unique_ptr<Case>** cases;
    sf::Vector2f origin;
    std::vector<int> seenRooms;
    std::vector<int> openedDoors;
    float offset;
public:
    Carte(int nbLines, int nbColumns, sf::Vector2f origin, float offset);
    Case* getCase(int x, int y);
    void addSeenRoom(int room);
    void addOpenedDoor(int doorId);
    void removeOpenedDoor(int doorId);
    void update(float dt);
    void draw(sf::RenderWindow &window);
    ~Carte() = default;
};
