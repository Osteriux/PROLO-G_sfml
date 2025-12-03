#include "game_manager.hpp"
#include "game_event.hpp"
#include "../game_object/static/interactible/interactible.hpp"
#include "../game_object/static/interactible/lever.hpp"

// Initialize static instance pointer
GameManager *GameManager::instance = nullptr;

GameManager::GameManager(sf::Vector2u windowSize, std::string filePath)
    : windowSize(windowSize)
{
    // Initialize event system first
    GameEventSystem::initialize();
    LevelFileData data = LevelFileHandeler::loadLevelFile(filePath);
    map = std::make_unique<Map>(data.mapHeight, data.mapWidth, sf::Vector2f((windowSize.x / 3) + 5, 5), sf::Vector2u((windowSize.x * 2 / 3) - 10, (windowSize.y * 2 / 3) - 10), data);
    map->populate(data);
    Case *c = map->getCase(data.playerX, data.playerY);
    std::unique_ptr<Player> j = std::make_unique<Player>(data.playerX, data.playerY, 5);
    player = j.get();
    c->setEntity(std::move(j));
    hud = std::make_unique<HUD>(sf::Vector2u(5, 5), sf::Vector2u((windowSize.x / 3) - 5, windowSize.y - 10));
    log = std::make_unique<Log>(50, sf::Vector2u((windowSize.x / 3) + 5, (windowSize.y * 2 / 3)), sf::Vector2u((windowSize.x * 2 / 3) - 10, (windowSize.y / 3) - 5));
}

void GameManager::initialize(sf::Vector2u windowSize, std::string filePath)
{
    if (instance != nullptr)
    {
        throw std::runtime_error("GameManager already initialized");
    }
    instance = new GameManager(windowSize, filePath);

    // Now that GameManager instance exists, init components that need event system
    instance->hud->init();
    instance->log->init();
    
    // Subscribe GameManager to HUD actions
    instance->getEventSystem().subscribe(GameEvent::Type::HUD_ACTION, instance);
    
    // Emit initial player state so HUD gets synchronized
    instance->player->emitInventoryChanged();
    instance->player->emitContextChanged();
}void GameManager::destroy()
{
    if (instance != nullptr)
    {
        // Unsubscribe GameManager from events
        GameEventSystem::getInstance().unsubscribeAll(instance);
        
        // Manually unsubscribe HUD and Log to avoid calling getInstance() after destruction
        if (instance->hud)
        {
            GameEventSystem::getInstance().unsubscribeAll(instance->hud.get());
        }
        if (instance->log)
        {
            GameEventSystem::getInstance().unsubscribeAll(instance->log.get());
        }
    }
    
    // Now safe to delete instance (won't call GameEventSystem in destructors)
    delete instance;
    instance = nullptr;
    
    // Destroy event system last
    GameEventSystem::destroy();
}

GameManager &GameManager::getInstance()
{
    if (instance == nullptr)
    {
        throw std::runtime_error("GameManager not initialized. Call initialize() first.");
    }
    return *instance;
}

GameEventSystem &GameManager::getEventSystem()
{
    return GameEventSystem::getInstance();
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

void GameManager::onEvent(const GameEvent &event)
{
    if (event.getType() == GameEvent::Type::HUD_ACTION)
    {
        const auto &hudEvent = static_cast<const HUDActionEvent &>(event);
        
        switch (hudEvent.getAction())
        {
        case HUDActionEvent::ActionType::MOVE_LEFT:
            player->move(Direction::LEFT);
            break;
        case HUDActionEvent::ActionType::MOVE_RIGHT:
            player->move(Direction::RIGHT);
            break;
        case HUDActionEvent::ActionType::MOVE_UP:
            player->move(Direction::UP);
            break;
        case HUDActionEvent::ActionType::MOVE_DOWN:
            player->move(Direction::DOWN);
            break;
        case HUDActionEvent::ActionType::USE_MINE:
            player->usePickup(Pickup::PickupType::MINE);
            break;
        case HUDActionEvent::ActionType::USE_BATTERY:
            player->usePickup(Pickup::PickupType::BATTERY);
            break;
        case HUDActionEvent::ActionType::USE_BOMB:
            player->usePickup(Pickup::PickupType::BOMB);
            break;
        case HUDActionEvent::ActionType::USE_DETECTOR:
            player->usePickup(Pickup::PickupType::DETECTOR);
            break;
        case HUDActionEvent::ActionType::USE_RADAR:
            // TODO: Implement radar functionality
            addLogMessage("Radar not yet implemented");
            break;
        case HUDActionEvent::ActionType::PICKUP_ITEM:
        {
            int index = hudEvent.getIndex();
            auto &pickups = player->getCase()->getPickups();
            if (index >= 0 && index < static_cast<int>(pickups.size()))
            {
                // TODO: Implement pickup collection
                addLogMessage("Pickup collection not yet implemented");
            }
            break;
        }
        case HUDActionEvent::ActionType::INTERACT_LEVER:
        {
            int index = hudEvent.getIndex();
            auto &interactibles = player->getCase()->getInteractibles();
            int currentIndex = 0;
            for (const auto &interactible : interactibles)
            {
                if (interactible->getType() == Interactible::InteractibleType::LEVER)
                {
                    if (currentIndex == index)
                    {
                        player->interactWithLever(static_cast<Lever *>(interactible.get()));
                        break;
                    }
                    currentIndex++;
                }
            }
            break;
        }
        default:
            break;
        }
    }
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
