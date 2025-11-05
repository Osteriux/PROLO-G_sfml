#include "bombe.h"
#include "../../dynamic/joueur/joueur.h"

Bombe::Bombe(int x, int y, GameManager* gameManager)
    : Item(std::make_unique<MultiTexture>(Item::texturePath(Item::BOMBE), 2), gameManager, x, y)
{
    type = ItemType::BOMBE;
}

std::string Bombe::getDescription() const
{
    return "Bombe";
}

void Bombe::action(DynamicGameObject* user)
{
    std::cout << "Bombe action" << std::endl;
}
