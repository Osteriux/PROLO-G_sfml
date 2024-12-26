#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "case.h"
#include "../factorys/item_factory.h"
#include "../utils/color/color_generator.h"
#include "../utils/fileReader/level_file_handeler.h"

class GameManager;

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
    std::vector<sf::Color> doorColors;
    sf::Vector2f origin;
    sf::Vector2f offset;
    std::map<int, bool> seenRooms;
    int nbLines, nbColumns;
    void updateCases();
public:
    Carte(int nbLines, int nbColumns, sf::Vector2f origin, sf::Vector2u regionSize, LevelFileData data);
    void populate(LevelFileData data, GameManager* gameManager);
    Case* getCase(int x, int y);
    std::map<std::pair<int, int>, std::map<Direction::Dir, bool>> getAdjacents();
    void addSeenRoom(int room);
    void scaleUp();
    void scaleDown();
    void move(sf::Vector2f offset);
    void reset();
    void update(float dt);
    void draw(sf::RenderWindow &window);
    ~Carte() = default;
    void debug();
};
