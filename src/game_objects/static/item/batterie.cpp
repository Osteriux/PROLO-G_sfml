#include "batterie.h"
#include "../../dynamic/joueur/joueur.h"

Batterie::Batterie(int x, int y, GameManager* gameManager)
    : Item(std::make_unique<MultiTexture>(Item::texturePath(Item::BATTERIE), 1), gameManager, x, y)
{
    type = ItemType::BATTERIE;
}

std::string Batterie::getDescription() const
{
    return "Batterie";
}

void Batterie::action(DynamicGameObject* user)
{
    std::cout << "Batterie action" << std::endl;
}
