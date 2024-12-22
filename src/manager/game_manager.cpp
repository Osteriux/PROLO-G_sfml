#include "game_manager.h"

GameManager::GameManager(sf::Vector2u windowSize, std::string filePath)
    : windowSize(windowSize)
{
    LevelFileData data = LevelFileHandeler::loadLevelFile(filePath);
    std::cout << "carte size : "<< data.hCarte << " " << data.wCarte << std::endl;
    carte = std::make_unique<Carte>(data.hCarte, data.wCarte, sf::Vector2f((windowSize.x / 3) + 5, 5), sf::Vector2u((windowSize.x * 2/3) - 10, (windowSize.y * 2/3) - 10), data);
    std::unique_ptr<Joueur> j = std::make_unique<Joueur>(this, data.joueurX, data.joueurY, 5, 1);
    joueur = j.get();
    hud = std::make_unique<HUD>(sf::Vector2u(5, 5), sf::Vector2u((windowSize.x / 3) - 5, windowSize.y - 10), joueur);
    log = std::make_unique<Log>(50, sf::Vector2u((windowSize.x / 3) + 5, (windowSize.y * 2/3)), sf::Vector2u((windowSize.x * 2/3) - 10, (windowSize.y / 3) - 5));
    carte->populate(data, std::move(j), this);
}

Joueur *GameManager::getJoueur()
{
    return joueur;
}

Carte *GameManager::getCarte()
{
    if(!carte.get()){
        throw std::runtime_error("Error: getCarte returned null");
    }
    return carte.get();
}

HUD &GameManager::getHUD()
{
    return *hud;
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
