#pragma once
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <iostream>
#include "GBMaps.h"
#include <sstream>
#include <algorithm>
#include <fstream>
#include <fstream>
#include <regex>
#include "GBMapLoader.h"

using namespace std;

GBMapLoader::GBMapLoader(int numOfPlayers, std::vector<Map::Node*> initTile)
{
    Map* testMap = new Map(numOfPlayers, initTile);
}

bool checkFile(std::string fileName)
{
    ifstream ifile(fileName);
    return ifile.good();
}

int checkValidPlayerNum(std::string file)
{
    ifstream ifile(file);
    std::string str;
    while (getline(ifile, str)) {
        if (str.find("Players:2") != std::string::npos)
        {
            cout << "The inputed value for the player is valid!\n";
            return 2;
        }
        if (str.find("Players:3") != std::string::npos)
        {
            cout << "The inputed value for the player is valid!\n";
            return 3;
        }
        if (str.find("Players:4") != std::string::npos)
        {
            cout << "The inputed value for the player is valid!\n";
            return 4;
        }
    }

    cout << "The inputed value for the player is invalid!\n";
    return 0;
}

std::vector<Map::Node*> checkValidTile(std::string file)
{
    ifstream ifile(file);
    std::string str;
    std::vector<Map::Node*>* initTile = new std::vector<Map::Node*>();
    while (getline(ifile, str)) {
        if (str.find("Tile:Stone,Sheep,Timber,Timber") != std::string::npos)
        {
            Map::Node* topLeft = new Map::Node(3, {}, false);
            Map::Node* topRight = new Map::Node(1, {}, false);
            Map::Node* bottomRight = new Map::Node(2, {}, false);
            Map::Node* bottomLeft = new Map::Node(2, {}, false);

            std::vector<Map::Node*>* topLeftAdj = new std::vector<Map::Node*>();
            topLeftAdj->push_back(topRight);
            topLeftAdj->push_back(bottomLeft);
            topLeft->setAdjNodes(topLeftAdj);

            std::vector<Map::Node*>* topRightAdj = new std::vector<Map::Node*>();
            topRightAdj->push_back(topLeft);
            topRightAdj->push_back(bottomRight);
            topRight->setAdjNodes(topRightAdj);

            std::vector<Map::Node*>* bottomLeftAdj = new std::vector<Map::Node*>();
            bottomLeftAdj->push_back(topLeft);
            bottomLeftAdj->push_back(bottomRight);
            bottomLeft->setAdjNodes(bottomLeftAdj);

            std::vector<Map::Node*>* bottomRightAdj = new std::vector<Map::Node*>();
            bottomRightAdj->push_back(topRight);
            bottomRightAdj->push_back(bottomLeft);
            bottomRight->setAdjNodes(bottomRightAdj);

            initTile->push_back(topLeft);
            initTile->push_back(topRight);
            initTile->push_back(bottomRight);
            initTile->push_back(bottomLeft);
            cout << "The inputed value for the tile is valid!\n";
            return* initTile;
        }

    }
    cout << "The inputed value for the tile is invalid!\n";
    return* initTile;
}
