#include "level_file_handeler.h"

std::vector<std::string> LevelFileHandeler::split(std::string str, char c)
{
	std::vector<std::string> v;
    if(c == '\0'){
        std::invalid_argument("delimiter can't be null character");
    }

    std::string buff{""};
    for(auto n:str)
    {
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != ""){
        v.push_back(buff);
    }
	
	return v;
}

LevelFileData LevelFileHandeler::loadLevelFile(std::string filePath)
{
    std::ifstream file(filePath);
    LevelFileData data;

    if(file.is_open()){
        std::vector<std::string> splitLine;
        std::string line;

        std::getline(file, line);
        std::cout << "loading level : " << line << std::endl;
        data.levelName = line;

        std::getline(file, line);
        std::cout << "room size : " << line << std::endl;
        splitLine = split(line, ' ');
        data.wCarte = std::stoi(splitLine[0]);
        data.hCarte = std::stoi(splitLine[1]);

        std::getline(file, line);
        std::cout << "number of door colors : " << line << std::endl;
        data.nbDoorColor = std::stoi(line);

        for(int i = 0; i < data.wCarte; i++){
            for(int j = 0; j < data.hCarte; j++){
                std::cout << "loading case : " << i << ":" << j << std::endl;
                std::getline(file, line);
                std::cout << "case data : " << line << std::endl;
                splitLine = split(line, ' ');
                int room = std::stoi(splitLine[0]);

                std::string voisinsStr = splitLine[1].erase(0, 1);
                std::vector<std::string> splitVoisins = split(voisinsStr, ',');
                std::vector<int> voisins;
                std::cout << "voisins : ";
                for(auto v : splitVoisins){
                    std::cout << v << " ";
                    voisins.push_back(std::stoi(v));
                }
                std::cout << std::endl;

                std::string portesStr = splitLine[2].erase(0, 1);
                std::vector<std::string> splitPortes = split(portesStr, ',');
                std::vector<std::tuple<int, int>> portes;
                std::cout << "portes : ";
                for(auto p : splitPortes){
                    std::cout << p << " ";
                    std::vector<std::string> splitPorte = split(p, ':');
                    portes.push_back(std::make_tuple(std::stoi(splitPorte[0]), std::stoi(splitPorte[1])));
                }
                std::cout << std::endl;
                
                data.casesData[std::make_pair(i, j)] = std::make_tuple(room, voisins, portes);
            }
        }

        std::getline(file, line);
        std::cout << "player position : " << line << std::endl;
        splitLine = split(line, ' ');
        data.joueurX = std::stoi(splitLine[0]);
        data.joueurY = std::stoi(splitLine[1]);

        std::getline(file, line);
        std::cout << "number of enemies : " << line << std::endl;
        data.nbEnemies = std::stoi(line);
        for (int i = 0; i < data.nbEnemies; i++){
            std::getline(file, line);
            std::cout << "enemy data : " << line << std::endl;
            std::vector<std::string> splitEnemy = split(line, ' ');
            data.enemiesData[std::make_pair(std::stoi(splitEnemy[0]), std::stoi(splitEnemy[1]))] = std::stoi(splitEnemy[2]);
        }

        std::getline(file, line);
        std::cout << "number of items : " << line << std::endl;
        data.nbItems = std::stoi(line);
        for(int i = 0; i < data.nbItems; i++){
            std::getline(file, line);
            std::cout << "item data : " << line << std::endl;
            std::vector<std::string> splitItem = split(line, ' ');
            data.itemsData[std::make_pair(std::stoi(splitItem[0]), std::stoi(splitItem[1]))] = std::vector<int>();
            std::vector<std::string> splitItemTypes = split(splitItem[2], ',');
            for(auto it : splitItemTypes){
                data.itemsData[std::make_pair(std::stoi(splitItem[0]), std::stoi(splitItem[1]))].push_back(std::stoi(it));
            }
        }

        std::getline(file, line);
        std::cout << "number of levers : " << line << std::endl;
        data.nbLevers = std::stoi(line);
        for(int i = 0; i < data.nbLevers; i++){
            std::getline(file, line);
            std::cout << "lever data : " << line << std::endl;
            std::vector<std::string> splitLever = split(line, ' ');
            data.leversData[std::make_pair(std::stoi(splitLever[0]), std::stoi(splitLever[1]))] = std::vector<int>();
            std::vector<std::string> splitLeverColors = split(splitLever[2], ',');
            for(auto lc : splitLeverColors){
                data.leversData[std::make_pair(std::stoi(splitLever[0]), std::stoi(splitLever[1]))].push_back(std::stoi(lc));
            }
        }

        file.close();
    }
    else{
        std::cerr << "Error loading file : " << filePath << std::endl;
    }
    return data;
}

void LevelFileHandeler::saveLevelFile(std::string filePath, LevelFileData data)
{
    std::cout << "TODO" << std::endl;
}