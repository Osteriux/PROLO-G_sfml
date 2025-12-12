#include "hud.hpp"
#include "../map/case.hpp"
#include "../game_object/static/pickup/pickup.hpp"
#include "../game_object/static/interactible/interactible.hpp"
#include "../game_object/static/interactible/lever.hpp"
#include "../manager/game_manager.hpp"
#include "../manager/game_event.hpp"
#include "../utils/logger/logger.hpp"

HUD::HUD(sf::Vector2u origin, sf::Vector2u size)
    : origin(origin), size(size),
      playerHealth(0), availableLeversOnCase(0),
      grid(sf::Vector2f(static_cast<float>(origin.x), static_cast<float>(origin.y)), 32, 32, sf::Vector2i(18, 15), sf::Vector2i(8, 7), 7, 13),
      leftArrow(grid.getCellPosition(0, 3), sf::Vector2f(32, 32), "assets/button/LEFT.png"),
      downArrow(grid.getCellPosition(1, 4), sf::Vector2f(32, 32), "assets/button/DOWN.png"),
      rightArrow(grid.getCellPosition(2, 3), sf::Vector2f(32, 32), "assets/button/RIGHT.png"),
      upArrow(grid.getCellPosition(1, 2), sf::Vector2f(32, 32), "assets/button/UP.png"),
      useRadar(grid.getCellPosition(1, 3), sf::Vector2f(32, 32), "assets/button/RADAR.png"),
      mineB(grid.getCellPosition(4, 2), sf::Vector2f(32, 32), "assets/hud/MINE.png"),
      batterieB(grid.getCellPosition(4, 3), sf::Vector2f(32, 32), "assets/hud/BATTERY.png"),
      bombeB(grid.getCellPosition(4, 4), sf::Vector2f(32, 32), "assets/hud/BOMB.png"),
      detecteurB(grid.getCellPosition(4, 5), sf::Vector2f(32, 32), "assets/hud/DETECTOR.png")
{
    Logger::log("HUD Grid Total Size: " + std::to_string(grid.getTotalWidth()) + "x" + std::to_string(grid.getTotalHeight()), Logger::INFO);
    Logger::log("Allocated HUD space : " + std::to_string(size.x) + "x" + std::to_string(size.y), Logger::INFO);
    if (!font.loadFromFile("assets/font/arial.ttf"))
    {
        Logger::log("Error loading font : assets/font/arial.ttf", Logger::ERROR);
    }

    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color::White);
    outline.setOutlineThickness(2);
    outline.setPosition(sf::Vector2f(origin));
    outline.setSize(sf::Vector2f(size.x, size.y));

    heart.setSize(sf::Vector2f(32, 32));
    // heart.setPosition(sf::Vector2f(origin.x + 10, origin.y + 10));
    heart.setFillColor(sf::Color::Red);

    mineT.setFont(font);
    mineT.setCharacterSize(20);
    mineT.setFillColor(sf::Color::White);
    mineT.setPosition(grid.getCellPosition(5, 2) + sf::Vector2f(8, 10));
    mineT.setString("0");

    batterieT.setFont(font);
    batterieT.setCharacterSize(20);
    batterieT.setFillColor(sf::Color::White);
    batterieT.setPosition(grid.getCellPosition(5, 3) + sf::Vector2f(8, 10));
    batterieT.setString("0");

    bombeT.setFont(font);
    bombeT.setCharacterSize(20);
    bombeT.setFillColor(sf::Color::White);
    bombeT.setPosition(grid.getCellPosition(5, 4) + sf::Vector2f(8, 10));
    bombeT.setString("0");

    detecteurT.setFont(font);
    detecteurT.setCharacterSize(20);
    detecteurT.setFillColor(sf::Color::White);
    detecteurT.setPosition(grid.getCellPosition(5, 5) + sf::Vector2f(8, 10));
    detecteurT.setString("0");

    ramasserText.setFont(font);
    ramasserText.setCharacterSize(20);
    ramasserText.setFillColor(sf::Color::White);
    ramasserText.setPosition(grid.getCellPosition(0, 6));
    ramasserText.setString("Pick up:");

    interagireText.setFont(font);
    interagireText.setCharacterSize(24);
    interagireText.setFillColor(sf::Color::White);
    interagireText.setPosition(grid.getCellPosition(0, 8));
    interagireText.setString("Interact:");

    buttonsText.setFont(font);
    buttonsText.setCharacterSize(24);
    buttonsText.setFillColor(sf::Color::White);
    buttonsText.setPosition(grid.getCellPosition(0, 10));
    buttonsText.setString("Buttons: ON/OFF");

    // Configure dynamic containers using grid regions
    sf::FloatRect pickupRegion = grid.getRegion(0, 7, 7, 1);
    pickupActions.configure(
        sf::Vector2f(pickupRegion.left, pickupRegion.top),
        sf::Vector2f(pickupRegion.width, pickupRegion.height),
        sf::Vector2f(32, 32),
        8,
        LayoutMode::HORIZONTAL_LIST);

    sf::FloatRect interactRegion = grid.getRegion(0, 9, 7, 1);
    interactActions.configure(
        sf::Vector2f(interactRegion.left, interactRegion.top),
        sf::Vector2f(interactRegion.width, interactRegion.height),
        sf::Vector2f(32, 32),
        8,
        LayoutMode::HORIZONTAL_LIST);

    sf::FloatRect leverRegion = grid.getRegion(0, 11, 7, 2);
    buttonsActions.configure(
        sf::Vector2f(leverRegion.left, leverRegion.top),
        sf::Vector2f(leverRegion.width, leverRegion.height),
        sf::Vector2f(32, 32),
        8,
        LayoutMode::HORIZONTAL_LIST);
}

void HUD::init()
{
    // Subscribe to relevant game events
    GameEventSystem::getInstance().subscribe(GameEvent::Type::PLAYER_INVENTORY_CHANGED, this);
    GameEventSystem::getInstance().subscribe(GameEvent::Type::PLAYER_CONTEXT_CHANGED, this);
    GameEventSystem::getInstance().subscribe(GameEvent::Type::ITEM_PICKED_UP, this);
    GameEventSystem::getInstance().subscribe(GameEvent::Type::ITEM_USED, this);
    GameEventSystem::getInstance().subscribe(GameEvent::Type::PLAYER_DAMAGED, this);
    GameEventSystem::getInstance().subscribe(GameEvent::Type::PLAYER_HEALED, this);
}

void HUD::onClic(sf::Vector2f mousePosition)
{
    HUDActionEvent event(HUDActionEvent::ActionType::NONE); // Dummy init

    if (leftArrow.isClicked(mousePosition))
    {
        Logger::log("left", Logger::INFO);
        event = HUDActionEvent(HUDActionEvent::ActionType::MOVE_LEFT);
    }
    else if (downArrow.isClicked(mousePosition))
    {
        Logger::log("down", Logger::INFO);
        event = HUDActionEvent(HUDActionEvent::ActionType::MOVE_DOWN);
    }
    else if (rightArrow.isClicked(mousePosition))
    {
        Logger::log("right", Logger::INFO);
        event = HUDActionEvent(HUDActionEvent::ActionType::MOVE_RIGHT);
    }
    else if (upArrow.isClicked(mousePosition))
    {
        Logger::log("up", Logger::INFO);
        event = HUDActionEvent(HUDActionEvent::ActionType::MOVE_UP);
    }
    else if (useRadar.isClicked(mousePosition))
    {
        Logger::log("radar", Logger::INFO);
        event = HUDActionEvent(HUDActionEvent::ActionType::USE_RADAR);
    }
    else if (mineB.isClicked(mousePosition))
    {
        Logger::log("mine", Logger::INFO);
        event = HUDActionEvent(HUDActionEvent::ActionType::USE_MINE);
    }
    else if (batterieB.isClicked(mousePosition))
    {
        Logger::log("battery", Logger::INFO);
        event = HUDActionEvent(HUDActionEvent::ActionType::USE_BATTERY);
    }
    else if (bombeB.isClicked(mousePosition))
    {
        Logger::log("bomb", Logger::INFO);
        event = HUDActionEvent(HUDActionEvent::ActionType::USE_BOMB);
    }
    else if (detecteurB.isClicked(mousePosition))
    {
        Logger::log("detector", Logger::INFO);
        event = HUDActionEvent(HUDActionEvent::ActionType::USE_DETECTOR);
    }
    else
    {
        // Check pickup actions using container
        int clickedIndex = -1;
        if (pickupActions.handleClick(mousePosition, clickedIndex))
        {
            Logger::log("pickup item " + std::to_string(clickedIndex), Logger::INFO);
            event = HUDActionEvent(HUDActionEvent::ActionType::PICKUP_ITEM, clickedIndex);
        }
        // Check lever actions using container
        else if (buttonsActions.handleClick(mousePosition, clickedIndex))
        {
            Logger::log("button lever " + std::to_string(clickedIndex), Logger::INFO);
            event = HUDActionEvent(HUDActionEvent::ActionType::INTERACT_LEVER, clickedIndex);
        }
    }

    GameManager::getInstance().getEventSystem().dispatch(event);
}

void HUD::update(float dt)
{
    // Currently no dynamic elements needing per-frame updates
}

void HUD::draw(sf::RenderWindow &window)
{
    window.draw(outline);
    for (int h = 0; h < playerHealth; h++)
    {
        heart.setPosition(grid.getCellPosition(h + 1, 0) + sf::Vector2f(4, 4));
        window.draw(heart);
    }
    leftArrow.draw(window);
    downArrow.draw(window);
    rightArrow.draw(window);
    upArrow.draw(window);
    useRadar.draw(window);
    mineB.draw(window);
    window.draw(mineT);
    batterieB.draw(window);
    window.draw(batterieT);
    bombeB.draw(window);
    window.draw(bombeT);
    detecteurB.draw(window);
    window.draw(detecteurT);
    window.draw(ramasserText);
    pickupActions.draw(window);
    window.draw(interagireText);
    interactActions.draw(window);
    window.draw(buttonsText);
    buttonsActions.draw(window);
}

HUD::~HUD()
{
    // Note: GameManager::destroy() handles unsubscription before destroying event system
    // This is just a safety check if HUD is destroyed independently
}

void HUD::onEvent(const GameEvent &event)
{
    switch (event.getType())
    {
    case GameEvent::Type::PLAYER_INVENTORY_CHANGED:
    {
        const auto &invEvent = static_cast<const PlayerInventoryChangedEvent &>(event);
        mineT.setString(std::to_string(invEvent.getMineCount()));
        batterieT.setString(std::to_string(invEvent.getBatteryCount()));
        bombeT.setString(std::to_string(invEvent.getBombCount()));
        detecteurT.setString(std::to_string(invEvent.getDetectorCount()));
        break;
    }
    case GameEvent::Type::PLAYER_CONTEXT_CHANGED:
    {
        const auto &ctxEvent = static_cast<const PlayerContextChangedEvent &>(event);
        availablePickupsOnCase = ctxEvent.getAvailablePickups();
        availableLeversOnCase = ctxEvent.getLeverCount();

        // Update pickup actions from new context - container handles positioning
        pickupActions.clear();
        for (const auto &pickupType : availablePickupsOnCase)
        {
            pickupActions.addButton(
                ButtonImage(
                    sf::Vector2f(0, 0), // Position managed by container
                    sf::Vector2f(32, 32),
                    Pickup::texturePath(pickupType, true) // HUD-specific texture path
                    ));
        }

        // Update lever buttons from new context - container handles positioning
        buttonsActions.clear();
        for (int i = 0; i < availableLeversOnCase; i++)
        {
            buttonsActions.addButton(
                ButtonLever(
                    sf::Vector2f(0, 0), // Position managed by container
                    sf::Vector2f(32, 32),
                    sf::Color::White // Default color - would need more event data for actual colors
                    ));
        }
        break;
    }
    case GameEvent::Type::PLAYER_DAMAGED:
    {
        const auto &dmgEvent = static_cast<const PlayerDamagedEvent &>(event);
        playerHealth = dmgEvent.getCurrentHealth();
        break;
    }
    case GameEvent::Type::PLAYER_HEALED:
    {
        const auto &healEvent = static_cast<const PlayerHealedEvent &>(event);
        playerHealth = healEvent.getCurrentHealth();
        break;
    }
    case GameEvent::Type::ITEM_PICKED_UP:
    case GameEvent::Type::ITEM_USED:
    {
        // Could show feedback animation here
        break;
    }
    default:
        break;
    }
}