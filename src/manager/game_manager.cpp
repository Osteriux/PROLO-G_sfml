#include "game_manager.h"

GameManager::GameManager(sf::Vector2u windowSize)
    : windowSize(windowSize)
{
    carte = std::make_unique<Carte>(4, 6, sf::Vector2f((windowSize.x / 3) + 5, 5), 5, sf::Vector2u((windowSize.x * 2/3) - 10, (windowSize.y* 2/3) - 10));
    joueur = new Joueur(carte.get(), 0, 0, 5, 1);
    hud = std::make_unique<HUD>(sf::Vector2u(5, 5), sf::Vector2u((windowSize.x / 3) - 5, windowSize.y - 10), joueur);
    log = std::make_unique<Log>(50, sf::Vector2u((windowSize.x / 3) + 5, (windowSize.y * 2/3)), sf::Vector2u((windowSize.x * 2/3) - 10, (windowSize.y / 3) - 5));
}

Joueur *GameManager::getJoueur()
{
    return joueur;
}

Carte *GameManager::getCarte()
{
    return carte.get();
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