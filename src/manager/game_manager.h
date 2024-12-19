#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../carte/carte.h"
#include "../hud/hud.h"
#include "../hud/log.h"
#include "../game_objects/dynamic/joueur/joueur.h"
#include "../utils/fileReader/level_file_handeler.h"

class GameManager
{
private:
    sf::Vector2u windowSize;
    std::unique_ptr<Carte> carte;
    std::unique_ptr<HUD> hud;
    std::unique_ptr<Log> log;
    Joueur* joueur;
public:
    GameManager(sf::Vector2u windowSize);
    GameManager(sf::Vector2u windowSize, std::string filePath);
    Joueur* getJoueur();
    Carte* getCarte();
    HUD& getHUD();
    void update(float dt);
    void draw(sf::RenderWindow &window);
    ~GameManager() = default;
};
