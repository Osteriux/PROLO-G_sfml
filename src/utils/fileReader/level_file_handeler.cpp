#include "level_file_handeler.hpp"
#include <sstream>
#include "../logger/logger.hpp"

std::vector<std::string> LevelFileHandeler::split(std::string str, char c)
{
    std::vector<std::string> v;
    if (c == '\0')
    {
        Logger::log("Delimiter can't be null character", Logger::ERROR);
        throw std::invalid_argument("delimiter can't be null character");
    }

    std::string buff{""};
    for (auto n : str)
    {
        if (n != c)
            buff += n;
        else if (n == c && buff != "")
        {
            v.push_back(buff);
            buff = "";
        }
    }
    if (buff != "")
    {
        v.push_back(buff);
    }

    return v;
}

LevelFileData LevelFileHandeler::loadLevelFile(std::string filePath)
{
    std::ifstream file(filePath);
    LevelFileData data;

    if (file.is_open())
    {
        std::vector<std::string> splitLine;
        std::string line;

        std::getline(file, line);
        Logger::log("loading level : " + line, Logger::INFO);
        data.levelName = line;

        std::getline(file, line);
        Logger::log("room size : " + line, Logger::INFO);
        splitLine = split(line, ' ');
        data.mapWidth = std::stoi(splitLine[0]);
        data.mapHeight = std::stoi(splitLine[1]);

        std::getline(file, line);
        Logger::log("number of door colors : " + line, Logger::INFO);
        data.doorColorCount = std::stoi(line);

        for (int i = 0; i < data.mapWidth; i++)
        {
            for (int j = 0; j < data.mapHeight; j++)
            {
                Logger::log("loading case : " + std::to_string(i) + ":" + std::to_string(j), Logger::DEBUG);
                std::getline(file, line);
                Logger::log("case data : " + line, Logger::DEBUG);
                splitLine = split(line, ' ');
                int room = std::stoi(splitLine[0]);

                std::string voisinsStr = splitLine[1].erase(0, 1);
                std::vector<std::string> splitVoisins = split(voisinsStr, ',');
                std::vector<int> neighbors;
                Logger::log("neighbors : " + voisinsStr, Logger::DEBUG);
                std::stringstream neighborsStream(" ");
                for (auto v : splitVoisins)
                {
                    neighborsStream << v << " ";
                    neighbors.push_back(std::stoi(v));
                }
                Logger::log("neighbors parsed : " + neighborsStream.str(), Logger::DEBUG);

                std::string doorsStr = splitLine[2].erase(0, 1);
                std::vector<std::string> splitDoors = split(doorsStr, ',');
                std::vector<std::tuple<int, int>> doors;
                Logger::log("doors : " + doorsStr, Logger::DEBUG);
                std::stringstream doorsStream(" ");
                for (auto p : splitDoors)
                {
                    doorsStream << p << " ";
                    std::vector<std::string> splitDoor = split(p, ':');
                    doors.push_back(std::make_tuple(std::stoi(splitDoor[0]), std::stoi(splitDoor[1])));
                }
                Logger::log("doors parsed : " + doorsStream.str(), Logger::DEBUG);

                data.casesData[std::make_pair(i, j)] = std::make_tuple(room, neighbors, doors);
            }
        }

        std::getline(file, line);
        Logger::log("player position : " + line, Logger::DEBUG);
        splitLine = split(line, ' ');
        data.playerX = std::stoi(splitLine[0]);
        data.playerY = std::stoi(splitLine[1]);

        std::getline(file, line);
        Logger::log("number of enemies : " + line, Logger::DEBUG);
        data.enemyCount = std::stoi(line);
        for (int i = 0; i < data.enemyCount; i++)
        {
            std::getline(file, line);
            Logger::log("enemy data : " + line, Logger::DEBUG);
            std::vector<std::string> splitEnemy = split(line, ' ');
            data.enemiesData[std::make_pair(std::stoi(splitEnemy[0]), std::stoi(splitEnemy[1]))] = std::stoi(splitEnemy[2]);
        }

        std::getline(file, line);
        Logger::log("number of pickups : " + line, Logger::DEBUG);
        data.pickupCount = std::stoi(line);
        for (int i = 0; i < data.pickupCount; i++)
        {
            std::getline(file, line);
            Logger::log("pickup data : " + line, Logger::DEBUG);
            std::vector<std::string> splitPickup = split(line, ' ');
            data.pickupsData[std::make_pair(std::stoi(splitPickup[0]), std::stoi(splitPickup[1]))] = std::vector<int>();
            std::vector<std::string> splitPickupTypes = split(splitPickup[2], ',');
            for (auto it : splitPickupTypes)
            {
                data.pickupsData[std::make_pair(std::stoi(splitPickup[0]), std::stoi(splitPickup[1]))].push_back(std::stoi(it));
            }
        }

        std::getline(file, line);
        Logger::log("number of levers : " + line, Logger::DEBUG);
        data.leverCount = std::stoi(line);
        for (int i = 0; i < data.leverCount; i++)
        {
            std::getline(file, line);
            Logger::log("lever data : " + line, Logger::DEBUG);
            std::vector<std::string> splitLever = split(line, ' ');
            data.leversData[std::make_pair(std::stoi(splitLever[0]), std::stoi(splitLever[1]))] = std::vector<int>();
            std::vector<std::string> splitLeverColors = split(splitLever[2], ',');
            for (auto lc : splitLeverColors)
            {
                data.leversData[std::make_pair(std::stoi(splitLever[0]), std::stoi(splitLever[1]))].push_back(std::stoi(lc));
            }
        }

        file.close();
    }
    else
    {
        Logger::log("Error loading file : " + filePath, Logger::ERROR);
    }
    return data;
}

void LevelFileHandeler::saveLevelFile(std::string filePath, LevelFileData data)
{
    Logger::log("TODO", Logger::INFO);
}