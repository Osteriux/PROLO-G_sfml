#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../game_object/static/pickup/pickup.hpp"
#include "../manager/game_event_system.hpp"
#include "button/button_text.hpp"
#include "button/button_image.hpp"
#include "button/button_lever.hpp"

class HUD : public IEventListener
{
private:
    sf::RectangleShape outline;
    sf::Vector2u origin;
    sf::Vector2u size;
    sf::Font font;

    // HUD State (replaces direct Player access)
    int playerHealth;
    std::vector<Pickup::PickupType> availablePickupsOnCase;
    int availableLeversOnCase;

    sf::RectangleShape heart;

    ButtonImage mineB;
    sf::Text mineT;
    ButtonImage batterieB;
    sf::Text batterieT;
    ButtonImage bombeB;
    sf::Text bombeT;
    ButtonImage detecteurB;
    sf::Text detecteurT;

    ButtonImage leftArrow;
    ButtonImage downArrow;
    ButtonImage rightArrow;
    ButtonImage upArrow;
    ButtonImage useRadar;

    sf::Text ramasserText;
    std::vector<ButtonImage> pickupActions;

    sf::Text interagireText;
    std::vector<ButtonImage> interactActions;

    sf::Text buttonsText;
    std::vector<ButtonLever> buttonsActions;

public:
    HUD(sf::Vector2u origin, sf::Vector2u size);
    void init(); // Subscribe to events after GameManager is ready
    void onClic(sf::Vector2f mousePosition);
    void update(float dt);
    void draw(sf::RenderWindow &window);
    void onEvent(const GameEvent &event) override;
    ~HUD();
};
