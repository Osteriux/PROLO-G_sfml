#include "chien.h"

Chien::Chien(GameManager *gameManager, int x, int y)
    : Monstre(gameManager, Monstre::monstreTypeToString(Monstre::CHIEN), 100, 2, x, y)
{
}

std::string Chien::getDescription() const
{
    return "Chien";
}