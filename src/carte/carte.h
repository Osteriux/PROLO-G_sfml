#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "case.h"
#include "../utils/color/color_generator.h"

class Carte
{
private:
    sf::RenderTexture renderTexture;
    sf::Sprite sprite;
    sf::Vector2u regionSize;
    sf::Vector2f scale;
    static constexpr float MAX_SCALE = 10.0f;
    static constexpr float MIN_SCALE = 0.1f;
    sf::RectangleShape outline;
    std::vector<std::vector<std::unique_ptr<Case>>> cases;
    sf::Vector2f origin;
    sf::Vector2f offset;
    std::map<int, bool> seenRooms;
    std::vector<int> openedDoors;
    int nbLines, nbColumns;
    void updateCases();
public:
    Carte(int nbLines, int nbColumns, sf::Vector2f origin, sf::Vector2u regionSize);
    Carte(int nbLines, int nbColumns, sf::Vector2f origin, sf::Vector2u regionSize, std::map<std::pair<int, int>, std::tuple<int, std::vector<int>, std::vector<std::tuple<int, int>>>> casesData, int nbDoorColor);
    Case* getCase(int x, int y);
    void addSeenRoom(int room);
    void addOpenedDoor(int doorId);
    void removeOpenedDoor(int doorId);
    void scaleUp();
    void scaleDown();
    void move(sf::Vector2f offset);
    void reset();
    void update(float dt);
    void draw(sf::RenderWindow &window);
    ~Carte() = default;
};
