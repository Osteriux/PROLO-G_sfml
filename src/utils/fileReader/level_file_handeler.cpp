#include "level_file_handeler.hpp"

std::vector<std::string> LevelFileHandeler::split(std::string str, char c)
{
    std::vector<std::string> v;
    if (c == '\0')
    {
        std::invalid_argument("delimiter can't be null character");
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
        std::cout << "loading level : " << line << std::endl;
        data.levelName = line;

        std::getline(file, line);
        std::cout << "room size : " << line << std::endl;
        splitLine = split(line, ' ');
        data.mapWidth = std::stoi(splitLine[0]);
        data.mapHeight = std::stoi(splitLine[1]);

        std::getline(file, line);
        std::cout << "number of door colors : " << line << std::endl;
        data.doorColorCount = std::stoi(line);

        for (int i = 0; i < data.mapWidth; i++)
        {
            for (int j = 0; j < data.mapHeight; j++)
            {
                std::cout << "loading case : " << i << ":" << j << std::endl;
                std::getline(file, line);
                std::cout << "case data : " << line << std::endl;
                splitLine = split(line, ' ');
                int room = std::stoi(splitLine[0]);

                std::string voisinsStr = splitLine[1].erase(0, 1);
                std::vector<std::string> splitVoisins = split(voisinsStr, ',');
                std::vector<int> neighbors;
                std::cout << "neighbors : ";
                for (auto v : splitVoisins)
                {
                    std::cout << v << " ";
                    neighbors.push_back(std::stoi(v));
                }
                std::cout << std::endl;

                std::string doorsStr = splitLine[2].erase(0, 1);
                std::vector<std::string> splitDoors = split(doorsStr, ',');
                std::vector<std::tuple<int, int>> doors;
                std::cout << "doors : ";
                for (auto p : splitDoors)
                {
                    std::cout << p << " ";
                    std::vector<std::string> splitDoor = split(p, ':');
                    doors.push_back(std::make_tuple(std::stoi(splitDoor[0]), std::stoi(splitDoor[1])));
                }
                std::cout << std::endl;

                data.casesData[std::make_pair(i, j)] = std::make_tuple(room, neighbors, doors);
            }
        }

        std::getline(file, line);
        std::cout << "player position : " << line << std::endl;
        splitLine = split(line, ' ');
        data.playerX = std::stoi(splitLine[0]);
        data.playerY = std::stoi(splitLine[1]);

        std::getline(file, line);
        std::cout << "number of enemies : " << line << std::endl;
        data.enemyCount = std::stoi(line);
        for (int i = 0; i < data.enemyCount; i++)
        {
            std::getline(file, line);
            std::cout << "enemy data : " << line << std::endl;
            std::vector<std::string> splitEnemy = split(line, ' ');
            data.enemiesData[std::make_pair(std::stoi(splitEnemy[0]), std::stoi(splitEnemy[1]))] = std::stoi(splitEnemy[2]);
        }

        std::getline(file, line);
        std::cout << "number of pickups : " << line << std::endl;
        data.pickupCount = std::stoi(line);
        for (int i = 0; i < data.pickupCount; i++)
        {
            std::getline(file, line);
            std::cout << "pickup data : " << line << std::endl;
            std::vector<std::string> splitPickup = split(line, ' ');
            data.pickupsData[std::make_pair(std::stoi(splitPickup[0]), std::stoi(splitPickup[1]))] = std::vector<int>();
            std::vector<std::string> splitPickupTypes = split(splitPickup[2], ',');
            for (auto it : splitPickupTypes)
            {
                data.pickupsData[std::make_pair(std::stoi(splitPickup[0]), std::stoi(splitPickup[1]))].push_back(std::stoi(it));
            }
        }

        std::getline(file, line);
        std::cout << "number of levers : " << line << std::endl;
        data.leverCount = std::stoi(line);
        for (int i = 0; i < data.leverCount; i++)
        {
            std::getline(file, line);
            std::cout << "lever data : " << line << std::endl;
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
        std::cerr << "Error loading file : " << filePath << std::endl;
    }
    return data;
}

void LevelFileHandeler::saveLevelFile(std::string filePath, LevelFileData data)
{
    std::cout << "TODO" << std::endl;
}