#include "batterie.h"
#include "../../dynamic/joueur/joueur.h"

Batterie::Batterie(int x, int y, GameManager* gameManager)
    : Item("assets/static/BATTERIE.png", gameManager, x, y)
{
    type = ItemType::BATTERIE;
}

std::string Batterie::getDescription()
{
    return "Batterie";
}

void Batterie::action(DynamicGameObject* user)
{
    std::cout << "Batterie action" << std::endl;
}
