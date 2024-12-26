#include "detecteur.h"

Detecteur::Detecteur(int x, int y, GameManager* gameManager)
    : Item(std::make_unique<MultiTexture>(Item::texturePath(Item::DETECTEUR), 2, 3, std::vector({3, 3})), gameManager, x, y)
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