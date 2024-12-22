#pragma once
#include "../dynamic_game_object.h"
#include "inventaire.h"

class Joueur : public DynamicGameObject
{
private:
    Inventaire inventaire;
public:
    Joueur(Carte* carte, int x, int y, int health, float speed);
    Inventaire& getInventaire();
    std::string getDescription() override;
    void move(Direction::Dir direction);
    ~Joueur() = default;
};
