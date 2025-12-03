#pragma once
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

struct LevelFileData
{
    /// @brief The name of the level
    std::string levelName;
    /// @brief The width of map
    int mapWidth;
    /// @brief The height of map
    int mapHeight;
    /// @brief number of different door colors
    int doorColorCount;
    /// @brief The x position of the player
    int playerX;
    /// @brief The y position of the player
    int playerY;
    /// @brief The number of enemies
    int enemyCount;
    /// @brief The number of pickups
    int pickupCount;
    /// @brief The number of levers
    int leverCount;
    /// @brief The data of the cases
    ///  The key is the position of the case and the value is a tuple containing the room number, the neighboors direction and the doors direction and color
    std::map<std::pair<int, int>, std::tuple<int, std::vector<int>, std::vector<std::tuple<int, int>>>> casesData;
    /// @brief The data of the enemies
    ///  The tuple contains the x and y position of the enemy and the enemy type
    std::map<std::pair<int, int>, int> enemiesData;
    /// @brief The data of the pickups
    ///  The tuple contains the x and y position of the pickup and the pickup type
    std::map<std::pair<int, int>, std::vector<int>> pickupsData;
    /// @brief The data of the levers
    ///  The tuple contains the x and y position of the lever and the door color
    std::map<std::pair<int, int>, std::vector<int>> leversData;
};

class LevelFileHandeler
{
private:
    static std::vector<std::string> split(std::string str, char delimiter);

public:
    static LevelFileData loadLevelFile(std::string filePath);
    static void saveLevelFile(std::string filePath, LevelFileData data);
};
