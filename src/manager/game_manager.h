#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../hud/hud.h"
#include "../hud/log.h"
#include "../game_objects/dynamic/player/player.h"
#include "../utils/fileReader/level_file_handeler.h"
#include "../map/map.h"

class GameManager
{
private:
    sf::Vector2u windowSize;
    std::unique_ptr<Map> map;
    std::unique_ptr<HUD> hud;
    std::unique_ptr<Log> log;
    Player *player;

    static GameManager *instance;
    GameManager(sf::Vector2u windowSize, std::string filePath);
    // Delete copy constructor and assignment operator
    GameManager(const GameManager &) = delete;
    GameManager &operator=(const GameManager &) = delete;

public:
    static void initialize(sf::Vector2u windowSize, std::string filePath);
    static GameManager &getInstance();
    static void destroy();
    Player *getPlayer();
    Map *getMap();
    HUD &getHUD();
    void update(float dt);
    void draw(sf::RenderWindow &window);
    ~GameManager() = default;
    void debug();
};
