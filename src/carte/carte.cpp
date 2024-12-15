#include "carte.h"
#include "../game_objects/dynamic/dynamic_game_object.h"
#include "../game_objects/static/static_game_object.h"

Carte::Carte(int nbLines, int nbColumns, sf::Vector2f origin, float offset)
    : nbLines(nbLines), nbColumns(nbColumns), origin(origin), offset(offset)
{
    cases = new std::unique_ptr<Case>*[nbLines];
    for (int i = 0; i < nbLines; i++)
    {
        cases[i] = new std::unique_ptr<Case>[nbColumns];
        for (int j = 0; j < nbColumns; j++)
        {
            cases[i][j] = std::make_unique<Case>(j, i, 0);
            cases[i][j]->setPosition(sf::Vector2f((origin.x + offset) * j, (origin.y + offset) * i));
        }
    }
}

Case* Carte::getCase(int x, int y)
{
    if (x >= 0 && x < nbLines && y >= 0 && y < nbColumns)
    {
        return cases[x][y].get();
    }
    return nullptr;
}

void Carte::addSeenRoom(int room)
{
    seenRooms.push_back(room);
}

void Carte::addOpenedDoor(int doorId)
{
    openedDoors.push_back(doorId);
}

void Carte::removeOpenedDoor(int doorId)
{
    openedDoors.erase(std::remove(openedDoors.begin(), openedDoors.end(), doorId), openedDoors.end());
}

void Carte::update(float dt)
{
    for (int i = 0; i < nbLines; i++)
    {
        for (int j = 0; j < nbColumns; j++)
        {
            cases[i][j]->update(dt);
        }
    }
}

void Carte::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < nbLines; i++)
    {
        for (int j = 0; j < nbColumns; j++)
        {
            if(std::find(seenRooms.begin(), seenRooms.end(), cases[i][j]->getRoom()) != seenRooms.end()){
                cases[i][j]->draw(window);
            }
        }
    }
}