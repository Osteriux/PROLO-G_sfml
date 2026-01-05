#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../hud/hud.hpp"
#include "../hud/log.hpp"
#include "../game_object/dynamic/player/player.hpp"
#include "../utils/fileReader/level_file_handeler.hpp"
#include "../map/map.hpp"
#include "game_event_system.hpp"
#include "viewport_manager.hpp"

class GameManager : public IEventListener
{
private:
    std::unique_ptr<ViewportManager> viewportManager;
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
    void init();
    static GameManager &getInstance();
    static void destroy();
    GameEventSystem &getEventSystem();
    ViewportManager &getViewportManager();
    Player *getPlayer();
    Map *getMap();
    HUD &getHUD();
    void addLogMessage(std::string message);
    void onWindowResized(sf::Vector2u newSize);
    void update(float dt);
    void draw(sf::RenderWindow &window);
    void onEvent(const GameEvent &event) override;
    ~GameManager() = default;
};
