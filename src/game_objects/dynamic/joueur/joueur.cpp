#include "../../../manager/game_manager.h"
#include "joueur.h"

Joueur::Joueur(GameManager* gameManager, int x, int y, int health, float speed)
    : DynamicGameObject(health, speed, std::make_unique<MultiTexture>("assets/dynamic/JOUEUR.png", 1), gameManager, x, y), inventaire()
{
}

Inventaire& Joueur::getInventaire()
{
    return inventaire;
}

std::string Joueur::getDescription()
{
    return "Joueur";
}

void Joueur::move(Direction::Dir direction)
{
    DynamicGameObject::move(direction);
}