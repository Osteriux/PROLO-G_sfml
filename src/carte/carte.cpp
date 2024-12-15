#include "carte.h"
#include "../game_objects/dynamic/dynamic_game_object.h"
#include "../game_objects/static/static_game_object.h"

Carte::Carte(int nbLines, int nbColumns, sf::Vector2f origin, float offset, sf::Vector2u regionSize)
    : nbLines(nbLines), nbColumns(nbColumns), origin(origin), offset(offset), regionSize(regionSize), scale(1, 1)
{
    cases.resize(nbLines);
    for(int i = 0; i < nbLines; i++){
        cases[i].resize(nbColumns);
        for(int j = 0; j < nbColumns; j++){
            cases[i][j] = std::make_unique<Case>(i, j, 0, origin + sf::Vector2f(j * (offset + Case::SIZE), i * (offset + Case::SIZE)));
        }
    }
    seenRooms.push_back(0);
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color::White);
    outline.setOutlineThickness(2);
    outline.setPosition(origin);
    outline.setSize(sf::Vector2f(regionSize.x, regionSize.y));
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

void Carte::scaleUp()
{
    scale.x += 0.1;
    scale.y += 0.1;
    for (int i = 0; i < nbLines; i++)
    {
        for (int j = 0; j < nbColumns; j++)
        {
            cases[i][j]->setScale(scale);
            cases[i][j]->setPosition(origin + sf::Vector2f(j * (offset + Case::SIZE) * scale.x, i * (offset + Case::SIZE) * scale.y));
        }
    }
}

void Carte::scaleDown()
{
    scale.x -= 0.1;
    scale.y -= 0.1;
    for (int i = 0; i < nbLines; i++)
    {
        for (int j = 0; j < nbColumns; j++)
        {
            cases[i][j]->setScale(scale);
            cases[i][j]->setPosition(origin + sf::Vector2f(j * (offset + Case::SIZE) * scale.x, i * (offset + Case::SIZE) * scale.y));
        }
    }
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
    // Save the original view
    sf::View originalView = window.getView();

    // Create a view that matches the outline's position and size
    sf::View view(sf::FloatRect(origin.x, origin.y, outline.getSize().x, outline.getSize().y));
    view.setCenter(origin.x + outline.getSize().x / 2, origin.y + outline.getSize().y / 2);
    window.setView(view);

    // Draw the outline
    window.draw(outline);

    // Draw the cases within the outline
    for (int i = 0; i < nbLines; i++)
    {
        for (int j = 0; j < nbColumns; j++)
        {
            if (std::find(seenRooms.begin(), seenRooms.end(), cases[i][j]->getRoom()) != seenRooms.end())
            {
                cases[i][j]->draw(window);
            }
        }
    }

    // Restore the original view
    window.setView(originalView);
}