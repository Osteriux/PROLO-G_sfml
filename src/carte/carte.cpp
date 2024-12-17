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
            cases[i][j] = std::make_unique<Case>(i, j, 0, origin + sf::Vector2f(j * (offset + Case::SIZE), i * (offset + Case::SIZE)), std::vector<Direction::Dir>(), std::map<Direction::Dir, sf::Color>());
        }
    }
    renderTexture.create(regionSize.x, regionSize.y);
    texture = renderTexture.getTexture();
    sprite.setTexture(texture);
    sprite.setPosition(origin);
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
    // Clear the render texture
    renderTexture.clear(sf::Color::Transparent);

    // Set the view of the render texture to match the region
    sf::View view(sf::FloatRect(origin.x, origin.y, regionSize.x, regionSize.y));
    renderTexture.setView(view);

    // Draw the outline to the render texture
    renderTexture.draw(outline);

    // Draw the cases within the outline to the render texture
    for (int i = 0; i < nbLines; i++)
    {
        for (int j = 0; j < nbColumns; j++)
        {
            if (std::find(seenRooms.begin(), seenRooms.end(), cases[i][j]->getRoom()) != seenRooms.end())
            {
                cases[i][j]->draw(renderTexture);
            }
        }
    }

    // Display the render texture
    renderTexture.display();

    // Create a sprite from the render texture
    texture = renderTexture.getTexture();
    sprite.setTexture(texture);

    // Draw the sprite to the window
    window.draw(sprite);

    // Draw the outline to the window
    window.draw(outline);
}