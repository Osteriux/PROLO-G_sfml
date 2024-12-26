#include "../game_objects/dynamic/dynamic_game_object.h"
#include "../game_objects/static/static_game_object.h"
#include "../manager/game_manager.h"
#include "carte.h"

Carte::Carte(int nbLines, int nbColumns, sf::Vector2f origin, sf::Vector2u regionSize, LevelFileData levelData)
    : origin(origin), regionSize(regionSize), scale(1, 1)
{
    this->nbLines = nbLines;
    this->nbColumns = nbColumns;
    std::vector<sf::Color> doorColors = ColorGenerator::generateColors(levelData.nbDoorColor);
    cases.resize(nbLines);
    for(int i = 0; i < nbLines; i++){
        cases[i].resize(nbColumns);
        for(int j = 0; j < nbColumns; j++){
            std::tuple<int, std::vector<int>, std::vector<std::tuple<int, int>>> cdata = levelData.casesData[std::make_pair(i, j)];

            std::vector<Direction::Dir> voisins;
            std::map<Direction::Dir, sf::Color> portes;
            for(auto v : std::get<1>(cdata)){
                voisins.push_back(Direction::intToDir(v));
            }
            for(auto p : std::get<2>(cdata)){
                portes[Direction::intToDir(std::get<0>(p))] = doorColors[std::get<1>(p)];
            }
            std::cout << "Creating case : " << i << " " << j << " " << std::get<0>(cdata) << std::endl;
            cases[i][j] = std::make_unique<Case>(i, j, std::get<0>(cdata), origin + sf::Vector2f(j * Case::SIZE, i * Case::SIZE), voisins, portes);

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
    std::cout << "Carte created" << std::endl;
    std::cout << "Carte size : " << this->nbLines << " " << this->nbColumns << std::endl;
}

void Carte::populate(LevelFileData levelData, GameManager* gameManager)
{
    std::cout << "Populating carte" << std::endl;
    for(auto itemData : levelData.itemsData){
        for(int itemTypeId : itemData.second){
            cases[itemData.first.first][itemData.first.second]->addItem(ItemFactory::createItem(itemData.first.first, itemData.first.second, itemTypeId, gameManager));
        }
    }
    std::cout << "Carte populated" << std::endl;
}

Case* Carte::getCase(int x, int y)
{
    if (x >= 0 && x < nbLines && y >= 0 && y < nbColumns)
    {
        Case* c = cases[x][y].get();
        if(c == nullptr){
            std::cerr << "Error: getCase returned null" << std::endl;
        }
        return c;
    }
    std::cerr << "Error: getCase out of bounds : " + std::to_string(x) + " " + std::to_string(y) + " / " + std::to_string(nbLines) + " " + std::to_string(nbColumns) << std::endl;
    return nullptr;
}

std::map<std::pair<int, int>, std::map<Direction::Dir, bool>> Carte::getAdjacents()
{
    std::map<std::pair<int, int>, std::map<Direction::Dir, bool>> adjacents;
    for(int i = 0; i < nbLines; i++){
        for(int j = 0; j < nbColumns; j++){
            adjacents[std::make_pair(i, j)] = cases[i][j]->getAdjacent();
        }
    }
    return adjacents;
}

void Carte::addSeenRoom(int room)
{
    seenRooms[room] = true;
}

void Carte::scaleUp()
{
    if(scale.x + 0.1 > MAX_SCALE || scale.y + 0.1 > MAX_SCALE){
        return;
    }
    scale.x += 0.1;
    scale.y += 0.1;
    updateCases();
}

void Carte::scaleDown()
{
    if(scale.x - 0.1 < MIN_SCALE || scale.y - 0.1 < MIN_SCALE){
        return;
    }
    scale.x -= 0.1;
    scale.y -= 0.1;
    updateCases();
}

void Carte::move(sf::Vector2f offset)
{
    this->offset += offset;
    updateCases();
}

void Carte::reset()
{
    offset = sf::Vector2f(0, 0);
    scale = sf::Vector2f(1, 1);
    updateCases();
}

void Carte::updateCases()
{
    for (int i = 0; i < nbLines; i++)
    {
        for (int j = 0; j < nbColumns; j++)
        {
            cases[i][j]->setPosition(origin + sf::Vector2f(j * Case::SIZE * scale.x, i * Case::SIZE * scale.y) + offset);
            cases[i][j]->setScale(scale);
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

    // Draw the cases within the outline to the render texture
    for (int i = 0; i < nbLines; i++)
    {
        for (int j = 0; j < nbColumns; j++)
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

void Carte::debug()
{
    std::cout << "Carte size : " << this->nbLines << " " << this->nbColumns << std::endl;
}