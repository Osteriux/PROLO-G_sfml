#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../game_object/dynamic/player/player.hpp"
#include "../game_object/static/pickup/pickup.hpp"
#include "button/button_text.hpp"
#include "button/button_image.hpp"
#include "button/button_lever.hpp"

class HUD
{
private:
    sf::RectangleShape outline;
    Player *player;
    sf::Vector2u origin;
    sf::Vector2u size;
    sf::Font font;

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
    HUD(sf::Vector2u origin, sf::Vector2u size, Player *player);
    void onClic(sf::Vector2f mousePosition);
    void update(float dt);
    void draw(sf::RenderWindow &window);
    ~HUD() = default;
};
