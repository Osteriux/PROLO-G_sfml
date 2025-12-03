#include "game_manager.hpp"

// Initialize static instance pointer
GameManager *GameManager::instance = nullptr;

GameManager::GameManager(sf::Vector2u windowSize, std::string filePath)
    : windowSize(windowSize)
{
    LevelFileData data = LevelFileHandeler::loadLevelFile(filePath);
    map = std::make_unique<Map>(data.mapHeight, data.mapWidth, sf::Vector2f((windowSize.x / 3) + 5, 5), sf::Vector2u((windowSize.x * 2 / 3) - 10, (windowSize.y * 2 / 3) - 10), data);
    map->populate(data);
    Case *c = map->getCase(data.playerX, data.playerY);
    std::unique_ptr<Player> j = std::make_unique<Player>(data.playerX, data.playerY, 5);
    player = j.get();
    c->setEntity(std::move(j));
    hud = std::make_unique<HUD>(sf::Vector2u(5, 5), sf::Vector2u((windowSize.x / 3) - 5, windowSize.y - 10), player);
    log = std::make_unique<Log>(50, sf::Vector2u((windowSize.x / 3) + 5, (windowSize.y * 2 / 3)), sf::Vector2u((windowSize.x * 2 / 3) - 10, (windowSize.y / 3) - 5));
}

void GameManager::initialize(sf::Vector2u windowSize, std::string filePath)
{
    if (instance != nullptr)
    {
        throw std::runtime_error("GameManager already initialized");
    }
    instance = new GameManager(windowSize, filePath);
}

GameManager &GameManager::getInstance()
{
    if (instance == nullptr)
    {
        throw std::runtime_error("GameManager not initialized. Call initialize() first.");
    }
    return *instance;
}

void GameManager::destroy()
{
    delete instance;
    instance = nullptr;
}

Player *GameManager::getPlayer()
{
    return player;
}

Map *GameManager::getMap()
{
    return map.get();
}

HUD &GameManager::getHUD()
{
    return *hud;
}

void GameManager::addLogMessage(std::string message)
{
    log->addMessage(message);
}

void GameManager::update(float dt)
{
    map->update(dt);
    hud->update(dt);
}

void GameManager::draw(sf::RenderWindow &window)
{
    map->draw(window);
    hud->draw(window);
    log->draw(window);
}

void GameManager::debug()
{
    std::cout << "GameManager getMap" << std::endl;
    map->debug();
    std::cout << "GameManager getMap end" << std::endl;
    Map *c = map.get();
    c->debug();
    std::cout << "GameManager getMap end 2" << std::endl;
}
