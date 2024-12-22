#include "joueur.h"

Joueur::Joueur(Carte* carte, int x, int y, int health, float speed)
    : DynamicGameObject(health, speed, std::make_unique<MultiTexture>("assets/dynamic/JOUEUR.png", 1), carte, x, y), inventaire()
{
    currCase->setEntity(std::unique_ptr<Joueur>(this));
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