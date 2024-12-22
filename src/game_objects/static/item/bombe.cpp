#include "bombe.h"
#include "../../dynamic/joueur/joueur.h"

Bombe::Bombe(int x, int y, GameManager* gameManager)
    : Item("assets/static/BOMBE.png", gameManager, x, y)
{
    type = ItemType::BOMBE;
}

std::string Bombe::getDescription()
{
    return "Bombe";
}

void Bombe::action(DynamicGameObject* user)
{
    std::cout << "Bombe action" << std::endl;
}
