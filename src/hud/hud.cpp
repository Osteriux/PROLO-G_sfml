#include "hud.hpp"
#include "../map/case.hpp"
#include "../game_object/static/pickup/pickup.hpp"
#include "../game_object/static/interactible/interactible.hpp"
#include "../game_object/static/interactible/lever.hpp"
#include "../manager/game_manager.hpp"
#include "../manager/game_event.hpp"

HUD::HUD(sf::Vector2u origin, sf::Vector2u size)
    : origin(origin), size(size),
      playerHealth(0), availableLeversOnCase(0),
      leftArrow(sf::Vector2f(origin.x + 10, origin.y + 110), sf::Vector2f(32, 32), "assets/button/LEFT.png"),
      downArrow(sf::Vector2f(origin.x + 50, origin.y + 150), sf::Vector2f(32, 32), "assets/button/DOWN.png"),
      rightArrow(sf::Vector2f(origin.x + 90, origin.y + 110), sf::Vector2f(32, 32), "assets/button/RIGHT.png"),
      upArrow(sf::Vector2f(origin.x + 50, origin.y + 70), sf::Vector2f(32, 32), "assets/button/UP.png"),
      useRadar(sf::Vector2f(origin.x + 50, origin.y + 110), sf::Vector2f(32, 32), "assets/button/RADAR.png"),
      mineB(sf::Vector2f(origin.x + 140, origin.y + 90), sf::Vector2f(32, 32), "assets/hud/MINE.png"),
      batterieB(sf::Vector2f(origin.x + 200, origin.y + 90), sf::Vector2f(32, 32), "assets/hud/BATTERY.png"),
      bombeB(sf::Vector2f(origin.x + 140, origin.y + 130), sf::Vector2f(32, 32), "assets/hud/BOMB.png"),
      detecteurB(sf::Vector2f(origin.x + 200, origin.y + 130), sf::Vector2f(32, 32), "assets/hud/DETECTOR.png")
{
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
    mineT.setPosition(sf::Vector2f(origin.x + 180, origin.y + 100));
    mineT.setString("0");

    batterieT.setFont(font);
    batterieT.setCharacterSize(20);
    batterieT.setFillColor(sf::Color::White);
    batterieT.setPosition(sf::Vector2f(origin.x + 240, origin.y + 100));
    batterieT.setString("0");

    bombeT.setFont(font);
    bombeT.setCharacterSize(20);
    bombeT.setFillColor(sf::Color::White);
    bombeT.setPosition(sf::Vector2f(origin.x + 180, origin.y + 140));
    bombeT.setString("0");

    detecteurT.setFont(font);
    detecteurT.setCharacterSize(20);
    detecteurT.setFillColor(sf::Color::White);
    detecteurT.setPosition(sf::Vector2f(origin.x + 240, origin.y + 140));
    detecteurT.setString("0");

    ramasserText.setFont(font);
    ramasserText.setCharacterSize(20);
    ramasserText.setFillColor(sf::Color::White);
    ramasserText.setPosition(sf::Vector2f(origin.x + 10, origin.y + 190));
    ramasserText.setString("Pick up:");
    // pickupActions.push_back(ButtonImage(sf::Vector2f(origin.x + 10, origin.y + 310), sf::Vector2f(32,32), "assets/button/ITEM.png"));

    interagireText.setFont(font);
    interagireText.setCharacterSize(24);
    interagireText.setFillColor(sf::Color::White);
    interagireText.setPosition(sf::Vector2f(origin.x + 10, origin.y + 350));
    interagireText.setString("Interact:");
    // interactActions.push_back(ButtonImage(sf::Vector2f(origin.x + 10, origin.y + 390), sf::Vector2f(32,32), "assets/button/ITEM.png"));

    buttonsText.setFont(font);
    buttonsText.setCharacterSize(24);
    buttonsText.setFillColor(sf::Color::White);
    buttonsText.setPosition(sf::Vector2f(origin.x + 10, origin.y + 430));
    buttonsText.setString("Buttons: ON/OFF");
    // buttonsActions.push_back(ButtonLever(sf::Vector2f(origin.x + 10, origin.y + 470), sf::Vector2f(32,32), "assets/button/ITEM.png"));
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
        // Check pickup actions
        for (size_t i = 0; i < pickupActions.size(); i++)
        {
            if (pickupActions[i].isClicked(mousePosition))
            {
                std::cout << "pickup item " << i << std::endl;
                event = HUDActionEvent(HUDActionEvent::ActionType::PICKUP_ITEM, i);
                break;
            }
        }

        // Check lever actions
        for (size_t i = 0; i < buttonsActions.size(); i++)
        {
            if (buttonsActions[i].isClicked(mousePosition))
            {
                std::cout << "button lever " << i << std::endl;
                event = HUDActionEvent(HUDActionEvent::ActionType::INTERACT_LEVER, i);
                break;
            }
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
        heart.setPosition(sf::Vector2f(origin.x + 10 + h * 50, origin.y + 10));
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
    for (auto &action : pickupActions)
    {
        action.draw(window);
    }
    window.draw(interagireText);
    for (auto &action : interactActions)
    {
        action.draw(window);
    }
    window.draw(buttonsText);
    for (auto &action : buttonsActions)
    {
        action.draw(window);
    }
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

        // Update pickup actions from new context
        pickupActions.clear();
        int offsetY = 0;
        for (const auto &pickupType : availablePickupsOnCase)
        {
            pickupActions.emplace_back(
                sf::Vector2f(origin.x + 10, origin.y + 220 + offsetY),
                sf::Vector2f(32, 32),
                Pickup::texturePath(pickupType));
            offsetY += 40;
        }

        // Update lever buttons from new context
        buttonsActions.clear();
        for (int i = 0; i < availableLeversOnCase; i++)
        {
            buttonsActions.emplace_back(
                sf::Vector2f(origin.x + 10, origin.y + 460 + (i * 40)),
                sf::Vector2f(32, 32),
                sf::Color::White); // Default color - would need more event data for actual colors
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