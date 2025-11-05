#include "monstre_factory.h"
#include "../game_objects/dynamic/monstre/chien.h"

std::unique_ptr<Monstre> MonstreFactory::createMonstre(GameManager *gameManager, Monstre::MonstreType type, int x, int y)
{
    switch (type)
    {
    case Monstre::CHIEN:
        return std::make_unique<Chien>(gameManager, x, y);
    case Monstre::HURLEUR:
        // return std::make_unique<Hurleur>(gameManager, x, y);
    case Monstre::RAMPANT:
        // return std::make_unique<Rampant>(gameManager, x, y);
    default:
        throw std::invalid_argument("Invalid monstre type");
    }
}