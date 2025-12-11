#include "hud.hpp"
#include "../map/case.hpp"
#include "../game_object/static/pickup/pickup.hpp"
#include "../game_object/static/interactible/interactible.hpp"
#include "../game_object/static/interactible/lever.hpp"
#include "../manager/game_manager.hpp"
#include "../manager/game_event.hpp"

HUD::HUD(sf::Vector2u origin, sf::Vector2u size) // base dispo = 320 * 540
    : origin(origin), size(size),
      playerHealth(0), availableLeversOnCase(0),
      grid(sf::Vector2f(static_cast<float>(origin.x + 1), static_cast<float>(origin.y + 1)), 32, 32, sf::Vector2i(12, 11), sf::Vector2i(5, 2), 8, 15),
      leftArrow(grid.getCellPosition(1, 4), sf::Vector2f(32, 32), "assets/button/LEFT.png"),
      downArrow(grid.getCellPosition(2, 5), sf::Vector2f(32, 32), "assets/button/DOWN.png"),
      rightArrow(grid.getCellPosition(3, 4), sf::Vector2f(32, 32), "assets/button/RIGHT.png"),
      upArrow(grid.getCellPosition(2, 3), sf::Vector2f(32, 32), "assets/button/UP.png"),
      useRadar(grid.getCellPosition(2, 4), sf::Vector2f(32, 32), "assets/button/RADAR.png"),
      mineB(grid.getCellPosition(5, 3), sf::Vector2f(32, 32), "assets/hud/MINE.png"),
      batterieB(grid.getCellPosition(5, 4), sf::Vector2f(32, 32), "assets/hud/BATTERY.png"),
      bombeB(grid.getCellPosition(5, 5), sf::Vector2f(32, 32), "assets/hud/BOMB.png"),
      detecteurB(grid.getCellPosition(5, 6), sf::Vector2f(32, 32), "assets/hud/DETECTOR.png")
{
    std::cout << "HUD Grid Total Size: " << grid.getTotalWidth() << "x" << grid.getTotalHeight() << std::endl;
    std::cout << "Allocated HUD space : " << size.x << "x" << size.y << std::endl;
    if (!font.loadFromFile("assets/font/arial.ttf"))
    {
        std::cerr << "Error loading font : assets/font/arial.ttf" << std::endl;
    }
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color::White);
    outline.setOutlineThickness(2);
    outline.setPosition(sf::Vector2f(origin));
    outline.setSize(sf::Vector2f(size.x, size.y));

    heart.setSize(sf::Vector2f(32, 32));
    heart.setPosition(sf::Vector2f(origin.x + 10, origin.y + 10));
    heart.setFillColor(sf::Color::Red);

    mineT.setFont(font);
    mineT.setCharacterSize(20);
    mineT.setFillColor(sf::Color::White);
    mineT.setPosition(grid.getCellPosition(6, 3) + sf::Vector2f(8, 10));
    mineT.setString("0");

    batterieT.setFont(font);
    batterieT.setCharacterSize(20);
    batterieT.setFillColor(sf::Color::White);
    batterieT.setPosition(grid.getCellPosition(6, 4) + sf::Vector2f(8, 10));
    batterieT.setString("0");

    bombeT.setFont(font);
    bombeT.setCharacterSize(20);
    bombeT.setFillColor(sf::Color::White);
    bombeT.setPosition(grid.getCellPosition(6, 5) + sf::Vector2f(8, 10));
    bombeT.setString("0");

    detecteurT.setFont(font);
    detecteurT.setCharacterSize(20);
    detecteurT.setFillColor(sf::Color::White);
    detecteurT.setPosition(grid.getCellPosition(6, 6) + sf::Vector2f(8, 10));
    detecteurT.setString("0");

    ramasserText.setFont(font);
    ramasserText.setCharacterSize(20);
    ramasserText.setFillColor(sf::Color::White);
    ramasserText.setPosition(grid.getCellPosition(0, 7));
    ramasserText.setString("Pick up:");

    interagireText.setFont(font);
    interagireText.setCharacterSize(24);
    interagireText.setFillColor(sf::Color::White);
    interagireText.setPosition(grid.getCellPosition(0, 9));
    interagireText.setString("Interact:");

    buttonsText.setFont(font);
    buttonsText.setCharacterSize(24);
    buttonsText.setFillColor(sf::Color::White);
    buttonsText.setPosition(grid.getCellPosition(0, 12));
    buttonsText.setString("Buttons: ON/OFF");

    // Configure dynamic containers using grid regions
    sf::FloatRect pickupRegion = grid.getRegion(0, 8, 8, 1);
    pickupActions.configure(
        sf::Vector2f(pickupRegion.left, pickupRegion.top),
        sf::Vector2f(pickupRegion.width, pickupRegion.height),
        sf::Vector2f(32, 32),
        8,
        LayoutMode::HORIZONTAL_LIST);

    sf::FloatRect interactRegion = grid.getRegion(0, 10, 8, 2);
    interactActions.configure(
        sf::Vector2f(interactRegion.left, interactRegion.top),
        sf::Vector2f(interactRegion.width, interactRegion.height),
        sf::Vector2f(32, 32),
        8,
        LayoutMode::HORIZONTAL_LIST);

    sf::FloatRect leverRegion = grid.getRegion(0, 13, 8, 2);
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
        std::cout << "left" << std::endl;
        event = HUDActionEvent(HUDActionEvent::ActionType::MOVE_LEFT);
    }
    else if (downArrow.isClicked(mousePosition))
    {
        std::cout << "down" << std::endl;
        event = HUDActionEvent(HUDActionEvent::ActionType::MOVE_DOWN);
    }
    else if (rightArrow.isClicked(mousePosition))
    {
        std::cout << "right" << std::endl;
        event = HUDActionEvent(HUDActionEvent::ActionType::MOVE_RIGHT);
    }
    else if (upArrow.isClicked(mousePosition))
    {
        std::cout << "up" << std::endl;
        event = HUDActionEvent(HUDActionEvent::ActionType::MOVE_UP);
    }
    else if (useRadar.isClicked(mousePosition))
    {
        std::cout << "radar" << std::endl;
        event = HUDActionEvent(HUDActionEvent::ActionType::USE_RADAR);
    }
    else if (mineB.isClicked(mousePosition))
    {
        std::cout << "mine" << std::endl;
        event = HUDActionEvent(HUDActionEvent::ActionType::USE_MINE);
    }
    else if (batterieB.isClicked(mousePosition))
    {
        std::cout << "battery" << std::endl;
        event = HUDActionEvent(HUDActionEvent::ActionType::USE_BATTERY);
    }
    else if (bombeB.isClicked(mousePosition))
    {
        std::cout << "bomb" << std::endl;
        event = HUDActionEvent(HUDActionEvent::ActionType::USE_BOMB);
    }
    else if (detecteurB.isClicked(mousePosition))
    {
        std::cout << "detector" << std::endl;
        event = HUDActionEvent(HUDActionEvent::ActionType::USE_DETECTOR);
    }
    else
    {
        // Check pickup actions using container
        int clickedIndex = -1;
        if (pickupActions.handleClick(mousePosition, clickedIndex))
        {
            std::cout << "pickup item " << clickedIndex << std::endl;
            event = HUDActionEvent(HUDActionEvent::ActionType::PICKUP_ITEM, clickedIndex);
        }
        // Check lever actions using container
        else if (buttonsActions.handleClick(mousePosition, clickedIndex))
        {
            std::cout << "button lever " << clickedIndex << std::endl;
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
        heart.setPosition(grid.getCellPosition(h + 1, 1) + sf::Vector2f(4, 4));
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