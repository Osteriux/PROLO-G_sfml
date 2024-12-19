#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../game_objects/dynamic/joueur/joueur.h"
#include "../game_objects/static/item/item.h"
#include "boutons/bouton_text.h"
#include "boutons/bouton_image.h"
#include "boutons/bouton_levier.h"

class HUD {
private:
    sf::RectangleShape outline;
    Joueur* joueur;
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
    std::vector<ButtonLevier> buttonsActions;
public:
    HUD(sf::Vector2u origin, sf::Vector2u size, Joueur* joueur);
    void onClic(sf::Vector2f mousePosition);
    void update(float dt);
    void draw(sf::RenderWindow &window);
    ~HUD() = default;
};
