#pragma once
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

struct LevelFileData{
    /// @brief The name of the level
    std::string levelName;
    /// @brief The width of map
    int wCarte;
    /// @brief The height of map
    int hCarte;
    /// @brief number of different door colors
    int nbDoorColor;
    /// @brief The x position of the player
    int joueurX;
    /// @brief The y position of the player
    int joueurY;
    /// @brief The number of enemies
    int nbEnemies;
    /// @brief The number of items
    int nbItems;
    /// @brief The number of levers
    int nbLevers;
    /// @brief The data of the cases
    ///  The key is the position of the case and the value is a tuple containing the room number, the neighboors direction and the doors direction and color
    std::map<std::pair<int, int>, std::tuple<int, std::vector<int>, std::vector<std::tuple<int, int>>>> casesData;
    /// @brief The data of the enemies
    ///  The tuple contains the x and y position of the enemy and the enemy type
    std::map<std::pair<int, int>, int> enemiesData;
    /// @brief The data of the items
    ///  The tuple contains the x and y position of the item and the item type
    std::map<std::pair<int, int>, std::vector<int>> itemsData;
    /// @brief The data of the levers
    ///  The tuple contains the x and y position of the lever and the door color
    std::map<std::pair<int, int>, std::vector<int>> leversData;
};

class LevelFileHandeler{
private:
    static std::vector<std::string> split(std::string str, char delimiter);
public:
    static LevelFileData loadLevelFile(std::string filePath);
    static void saveLevelFile(std::string filePath, LevelFileData data);
};
