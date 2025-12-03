#include "../game_object/dynamic/dynamic_game_object.hpp"
#include "../game_object/static/static_game_object.hpp"
#include "../manager/game_manager.hpp"
#include "map.hpp"

Map::Map(int lineCount, int columnCount, sf::Vector2f origin, sf::Vector2u regionSize, LevelFileData levelData)
    : origin(origin), regionSize(regionSize), scale(1, 1)
{
    this->lineCount = lineCount;
    this->columnCount = columnCount;
    doorColors = ColorGenerator::generateColors(levelData.doorColorCount);
    cases.resize(lineCount);
    for (int i = 0; i < lineCount; i++)
    {
        cases[i].resize(columnCount);
        for (int j = 0; j < columnCount; j++)
        {
            std::tuple<int, std::vector<int>, std::vector<std::tuple<int, int>>> cdata = levelData.casesData[std::make_pair(i, j)];

            std::vector<Direction::Dir> neighbors;
            std::map<Direction::Dir, sf::Color> doors;
            for (auto v : std::get<1>(cdata))
            {
                neighbors.push_back(Direction::intToDir(v));
            }
            for (auto p : std::get<2>(cdata))
            {
                doors[Direction::intToDir(std::get<0>(p))] = doorColors[std::get<1>(p)];
            }
            std::cout << "Creating case : " << i << " " << j << " " << std::get<0>(cdata) << std::endl;
            cases[i][j] = std::make_unique<Case>(i, j, std::get<0>(cdata), origin + sf::Vector2f(j * Case::SIZE, i * Case::SIZE), neighbors, doors);

            // debug
            seenRooms[std::get<0>(cdata)] = true;
        }
    }
    renderTexture.create(regionSize.x, regionSize.y);
    sprite.setTexture(renderTexture.getTexture());
    sprite.setPosition(origin);
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color::White);
    outline.setOutlineThickness(2);
    outline.setPosition(origin);
    outline.setSize(sf::Vector2f(regionSize.x, regionSize.y));
    std::cout << "Map created" << std::endl;
    std::cout << "Map size : " << this->lineCount << " " << this->columnCount << std::endl;
}

void Map::populate(LevelFileData levelData)
{
    std::cout << "Populating map" << std::endl;
    for (auto pickupData : levelData.pickupsData)
    {
        for (int pickupTypeId : pickupData.second)
        {
            cases[pickupData.first.first][pickupData.first.second]->addPickup(ItemFactory::createPickup(pickupData.first.first, pickupData.first.second, pickupTypeId));
        }
    }
    for (auto leverData : levelData.leversData)
    {
        int i = 0;
        for (int doorId : leverData.second)
        {
            cases[leverData.first.first][leverData.first.second]->addInteractible(ItemFactory::createLever(doorColors[doorId], leverData.first.first, leverData.first.second, doorId, i));
            i++;
        }
    }
    for (auto monsterData : levelData.enemiesData)
    {
        cases[monsterData.first.first][monsterData.first.second]->setEntity(MonsterFactory::createMonster(Monster::intToMonsterType(monsterData.second), monsterData.first.first, monsterData.first.second));
    }
    std::cout << "Map populated" << std::endl;
    updateCases();
}

Case *Map::getCase(int x, int y)
{
    if (x >= 0 && x < lineCount && y >= 0 && y < columnCount)
    {
        Case *c = cases[x][y].get();
        if (c == nullptr)
        {
            std::cerr << "Error: getCase returned null" << std::endl;
        }
        return c;
    }
    std::cerr << "Error: getCase out of bounds : " + std::to_string(x) + " " + std::to_string(y) + " / " + std::to_string(lineCount) + " " + std::to_string(columnCount) << std::endl;
    return nullptr;
}

std::map<std::pair<int, int>, std::map<Direction::Dir, bool>> Map::getAdjacents()
{
    std::map<std::pair<int, int>, std::map<Direction::Dir, bool>> adjacents;
    for (int i = 0; i < lineCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            adjacents[std::make_pair(i, j)] = cases[i][j]->getAdjacent();
        }
    }
    return adjacents;
}

void Map::addSeenRoom(int room)
{
    seenRooms[room] = true;
}

void Map::scaleUp()
{
    if (scale.x + 0.1 > MAX_SCALE || scale.y + 0.1 > MAX_SCALE)
    {
        return;
    }
    scale.x += 0.1;
    scale.y += 0.1;
    updateCases();
}

void Map::scaleDown()
{
    if (scale.x - 0.1 < MIN_SCALE || scale.y - 0.1 < MIN_SCALE)
    {
        return;
    }
    scale.x -= 0.1;
    scale.y -= 0.1;
    updateCases();
}

void Map::move(sf::Vector2f offset)
{
    this->offset += offset;
    updateCases();
}

void Map::reset()
{
    offset = sf::Vector2f(0, 0);
    scale = sf::Vector2f(1, 1);
    updateCases();
}

void Map::updateCases()
{
    for (int i = 0; i < lineCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            cases[i][j]->setPosition(origin + sf::Vector2f(j * Case::SIZE * scale.x, i * Case::SIZE * scale.y) + offset);
            cases[i][j]->setScale(scale);
        }
    }
}

void Map::update(float dt)
{
    for (int i = 0; i < lineCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            cases[i][j]->update(dt);
        }
    }
}

void Map::draw(sf::RenderWindow &window)
{
    // Clear the render texture
    renderTexture.clear(sf::Color::Transparent);

    // Set the view of the render texture to match the region
    sf::View view(sf::FloatRect(origin.x, origin.y, regionSize.x, regionSize.y));
    renderTexture.setView(view);

    // Draw the cases within the outline to the render texture
    for (int i = 0; i < lineCount; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            if (seenRooms[cases[i][j]->getRoom()])
            {
                cases[i][j]->draw(renderTexture);
            }
        }
    }

    // Draw the outline to the render texture
    renderTexture.draw(outline);

    // Display the render texture
    renderTexture.display();

    // Draw the sprite to the window
    window.draw(sprite);

    // Draw the outline to the window
    window.draw(outline);
}

void Map::debug()
{
    std::cout << "Map size : " << this->lineCount << " " << this->columnCount << std::endl;
}