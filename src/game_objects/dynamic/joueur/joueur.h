#pragma once
#include "../dynamic_game_object.h"
#include "inventaire.h"

class GameManager;

class Joueur : public DynamicGameObject
{
private:
    Inventaire inventaire;
public:
    Joueur(GameManager* gameManager, int x, int y, int health);
    Inventaire& getInventaire();
    std::string getDescription() const override;
    void move(Direction::Dir direction);
    ~Joueur() = default;
};
