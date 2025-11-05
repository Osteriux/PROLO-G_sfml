#pragma once
#include <memory>
#include "../game_objects/dynamic/monstre/monstre.h"

// Forward declaration to reduce header dependencies
class GameManager;

class MonstreFactory
{
public:
    static std::unique_ptr<Monstre> createMonstre(GameManager *gameManager, Monstre::MonstreType type, int x, int y);
};
