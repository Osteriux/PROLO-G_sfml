#include "debug_console.hpp"
#include "../manager/game_manager.hpp"
#include <iostream>

DebugConsole::DebugConsole(sf::Vector2f position) : isVisible(false), position(position)
{
    // Setup background
    background.setSize(sf::Vector2f(400, 300));
    background.setPosition(position);
    background.setFillColor(sf::Color(0, 0, 0, 200));
    background.setOutlineColor(sf::Color::Yellow);
    background.setOutlineThickness(2);
}

bool DebugConsole::loadFont(const std::string &fontPath)
{
    if (!font.loadFromFile(fontPath))
    {
        std::cerr << "Failed to load debug console font: " << fontPath << std::endl;
        return false;
    }

    helpText.setFont(font);
    helpText.setCharacterSize(14);
    helpText.setFillColor(sf::Color::White);
    helpText.setPosition(20, 20);

    std::string help = "DEBUG CONSOLE (F1 to toggle)\n\n";
    help += "Quick Events:\n";
    help += "1 - Damage Player (10 HP)\n";
    help += "2 - Heal Player (20 HP)\n";
    help += "3 - Add Items (+1 each)\n";
    help += "4 - Pickup Mine\n";
    help += "5 - Pickup Battery\n";
    help += "6 - Pickup Bomb\n";
    help += "7 - Pickup Detector\n";
    help += "8 - Toggle Door 1\n";
    help += "9 - Toggle Door 2\n";

    helpText.setString(help);
    helpText.setPosition(position.x + 20, position.y + 20);

    return true;
}

void DebugConsole::toggle()
{
    isVisible = !isVisible;
    std::cout << "Debug Console: " << (isVisible ? "ON" : "OFF") << std::endl;
}

bool DebugConsole::handleInput(const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        // F1 toggles console
        if (event.key.code == sf::Keyboard::F1)
        {
            toggle();
            return true;
        }

        // Only process other keys if console is visible
        if (!isVisible)
        {
            return false;
        }

        // Number keys fire events
        switch (event.key.code)
        {
        case sf::Keyboard::Num1:
            quickFirePlayerDamage();
            return true;
        case sf::Keyboard::Num2:
            quickFirePlayerHeal();
            return true;
        case sf::Keyboard::Num3:
            quickFireInventoryChange();
            return true;
        case sf::Keyboard::Num4:
            quickFireItemPickup(Pickup::PickupType::MINE);
            return true;
        case sf::Keyboard::Num5:
            quickFireItemPickup(Pickup::PickupType::BATTERY);
            return true;
        case sf::Keyboard::Num6:
            quickFireItemPickup(Pickup::PickupType::BOMB);
            return true;
        case sf::Keyboard::Num7:
            quickFireItemPickup(Pickup::PickupType::DETECTOR);
            return true;
        case sf::Keyboard::Num8:
            quickFireDoorToggle(1);
            return true;
        case sf::Keyboard::Num9:
            quickFireDoorToggle(2);
            return true;
        default:
            return false;
        }
    }
    return false;
}

void DebugConsole::draw(sf::RenderWindow &window)
{
    if (!isVisible)
    {
        return;
    }

    window.draw(background);
    window.draw(helpText);
}

void DebugConsole::quickFirePlayerDamage(int damage)
{
    Player *player = GameManager::getInstance().getPlayer();
    if (player)
    {
        int currentHealth = player->getHealth();
        PlayerDamagedEvent event(damage, currentHealth - damage, "Debug Console");
        GameEventSystem::getInstance().dispatch(event);
        std::cout << "[DEBUG] Fired PlayerDamagedEvent: " << damage << " damage\n";
    }
}

void DebugConsole::quickFirePlayerHeal(int healing)
{
    Player *player = GameManager::getInstance().getPlayer();
    if (player)
    {
        int currentHealth = player->getHealth();
        PlayerHealedEvent event(healing, currentHealth + healing);
        GameEventSystem::getInstance().dispatch(event);
        std::cout << "[DEBUG] Fired PlayerHealedEvent: " << healing << " healing\n";
    }
}

void DebugConsole::quickFireInventoryChange(int mine, int battery, int bomb, int detector)
{
    Player *player = GameManager::getInstance().getPlayer();
    if (player)
    {
        int currentMine = player->getInventory().getQuantity(Pickup::MINE) + mine;
        int currentBattery = player->getInventory().getQuantity(Pickup::BATTERY) + battery;
        int currentBomb = player->getInventory().getQuantity(Pickup::BOMB) + bomb;
        int currentDetector = player->getInventory().getQuantity(Pickup::DETECTOR) + detector;

        PlayerInventoryChangedEvent event(currentMine, currentBattery, currentBomb, currentDetector);
        GameEventSystem::getInstance().dispatch(event);
        std::cout << "[DEBUG] Fired PlayerInventoryChangedEvent\n";
    }
}

void DebugConsole::quickFireItemPickup(Pickup::PickupType type)
{
    Player *player = GameManager::getInstance().getPlayer();
    if (player)
    {
        int x = player->getCase()->getX();
        int y = player->getCase()->getY();

        ItemPickedUpEvent event(type, x, y);
        GameEventSystem::getInstance().dispatch(event);

        std::string itemName;
        switch (type)
        {
        case Pickup::PickupType::MINE:
            itemName = "Mine";
            break;
        case Pickup::PickupType::BATTERY:
            itemName = "Battery";
            break;
        case Pickup::PickupType::BOMB:
            itemName = "Bomb";
            break;
        case Pickup::PickupType::DETECTOR:
            itemName = "Detector";
            break;
        }

        std::cout << "[DEBUG] Fired ItemPickedUpEvent: " << itemName << "\n";
    }
}

void DebugConsole::quickFireDoorToggle(int doorId)
{
    // Fire door opened event
    DoorOpenedEvent event(doorId);
    GameEventSystem::getInstance().dispatch(event);
    std::cout << "[DEBUG] Fired DoorOpenedEvent: Door " << doorId << "\n";
}
