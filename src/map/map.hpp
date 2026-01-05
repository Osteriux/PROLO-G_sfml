#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "case.hpp"
#include "../factory/item_factory.hpp"
#include "../factory/monster_factory.hpp"
#include "../utils/color/color_generator.hpp"
#include "../utils/fileReader/level_file_handeler.hpp"

class GameManager;

class Map
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
    int lineCount, columnCount;
    void updateCases();

public:
    Map(int lineCount, int columnCount, sf::Vector2f origin, sf::Vector2u regionSize, LevelFileData data);
    void init();
    void populate(LevelFileData data);
    Case *getCase(int x, int y);
    std::map<std::pair<int, int>, std::map<Direction::Dir, bool>> getAdjacents();
    void addSeenRoom(int room);
    void scaleUp();
    void scaleDown();
    void move(sf::Vector2f offset);
    void reset();
    void update(float dt);
    void draw(sf::RenderWindow &window);
    ~Map() = default;
};
