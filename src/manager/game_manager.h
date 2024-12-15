#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../carte/carte.h"
#include "../hud/hud.h"
#include "../hud/log.h"
#include "../game_objects/dynamic/joueur/joueur.h"

class GameManager
{
private:
    std::unique_ptr<Carte> carte;
    std::unique_ptr<HUD> hud;
    std::unique_ptr<Log> log;
    Joueur* joueur;
public:
    GameManager();
    Joueur* getJoueur();
    void update(float dt);
    void draw(sf::RenderWindow &window);
    ~GameManager() = default;
};
