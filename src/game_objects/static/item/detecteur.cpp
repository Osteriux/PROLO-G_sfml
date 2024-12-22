#include "detecteur.h"

Detecteur::Detecteur(int x, int y, GameManager* gameManager)
    : Item("assets/static/DETECTEUR.png", gameManager, x, y)
{
    type = ItemType::DETECTEUR;
    charge = 0;
    active = false;
}

std::string Detecteur::getDescription()
{
    return "Detecteur";
}

void Detecteur::action(DynamicGameObject* user)
{
    std::cout << "Detecteur action" << std::endl;
}