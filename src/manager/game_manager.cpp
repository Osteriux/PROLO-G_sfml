#include "game_manager.h"

GameManager::GameManager()
{
    carte = std::make_unique<Carte>(4, 6, sf::Vector2f(160, 0), 5);
    joueur = new Joueur(carte.get(), 0, 0, 5, 1);
    hud = std::make_unique<HUD>(sf::Vector2f(0, 0), joueur);
    log = std::make_unique<Log>(50, sf::Vector2f(160, 180), sf::Vector2f(320, 90));
}

Joueur *GameManager::getJoueur()
{
    return joueur;
}

void GameManager::update(float dt)
{
    carte->update(dt);
    hud->update(dt);
}

void GameManager::draw(sf::RenderWindow &window)
{
    carte->draw(window);
    hud->draw(window);
    log->draw(window);
}