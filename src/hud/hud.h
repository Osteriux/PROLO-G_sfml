#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../game_object/dynamic/player/player.h"
#include "../game_object/static/pickup/pickup.h"
#include "button/button_text.h"
#include "button/button_image.h"
#include "button/button_lever.h"

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
    std::vector<ButtonImage> ramasserActions;

    sf::Text interagireText;
    std::vector<ButtonImage> interagireActions;

    sf::Text buttonsText;
    std::vector<ButtonLever> buttonsActions;

public:
    HUD(sf::Vector2u origin, sf::Vector2u size, Player *player);
    void onClic(sf::Vector2f mousePosition);
    void update(float dt);
    void draw(sf::RenderWindow &window);
    ~HUD() = default;
};
