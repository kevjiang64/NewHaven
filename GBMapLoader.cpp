#pragma once
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <iostream>
#include "Map.h"
#inlcude "MapLoader.h"

/**
 * MapLoader defualt contructor
 */


MapLoader::MapLoader(){
    
}

/**
 * MapLoader constructor
 * @param mapFile
 */
MapLoader::MapLoader(std::string mapFile) {
    pMapFile = new std::string(std::move(mapFile));
}

/**
 * Map loader copy constructor
 * @param toCopy
 */
MapLoader::MapLoader(const MapLoader &toCopy) {
    pMapFile = new std::string();
    *pMapFile = *toCopy.pMapFile;
}

/**
 * MapLoader destructor
 */
MapLoader::~MapLoader() {
    delete pMapFile;
}

/**
 * assignment operator
 */
void MapLoader::operator=(MapLoader& rhs) {
    this->pMapFile = rhs.pMapFile;
}

/**
 * Main method of the map loader. Parses the file and creates the map object
 * @return Map
 */
Map* MapLoader::readMapFile() {
    //for debug purposes, change to true to print errors and warnings
    bool verbose = false;
    //create file stream to read file line by line
    std::ifstream infile(*pMapFile);
    if(!infile || infile.peek() == EOF){
        return nullptr;
    }
    std::string line;

    //declare map info
    auto* playerNumber = new int();
    auto* pTileData = new std::vector<std::vector<std::string>>;
    auto* pMode = new std::string;

    //maintain counters for validation / error tracing
    auto* pLineCount = new int(0);
    auto* pTileCount = new int(0);
    auto* pValidMap = new bool(true);

    while (std::getline(infile, line)) {
        (*pLineCount)++;
        //will hold the words of each line (separated by spaces) in an array
        auto* pLineWords = new std::vector<std::string>;
        //ignore comments or empty lines
        if (line.empty() || line[0] == *";" || line[0] == *"\n" || line[0] == *"\r") {
            //do nothing, the line is empty or is a comment
            continue;
        } else {
            // strip every line of the \n and \r characters
            line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            splitLine(line, pLineWords);
            getPlayerNumber(playerNumber, pLineWords);

            if (checkSection(pMode, pLineWords)) {
                continue;
            }

            //read sections
            if (*pMode == "tiles") {
                if (validateTileLine(pTileCount, pLineWords, pLineCount, pValidMap, verbose)) {
                    pTileData->push_back(*pLineWords);
                }
                else {
                    return nullptr;
                }
            }
            
            else {
            //unknown mode error, will be ignored, non-critical
            if(verbose){
                std::cout << "\nLine " << *pLineCount << " - [WARNING] : the parser encountered an unknown mode. ";
                std::cout << " ::  " << line;
            }
        }
        
        delete(pLineWords);
    }
        //create map object

        auto* map = initMapObject(playerNumber, pTileData, pValidMap);

        //clean up
        delete (pMode);
        delete (pLineCount);
        delete (pTileCount);

        if(!*pValidMap || pContinentData->empty() || pCountryData->empty() || pBorderData->empty()){
            delete (pValidMap);
            delete (pTileData);
            delete (playerNumber);
            return nullptr;
        }
        delete (pValidMap);
        delete (pTileData);
        delete (playerNumber);
        return map;
}
    
/**
 * Helper function that creates the map object
 * @param playerNumber, integer of number of players
 * @param tileData, vector containing the nodes/resources of each tile
 * @param vMap, flags map validity
 * @return Map
*/
Map* MapLoader::initMapObject(int* playerNumber, std::vector<std::vector<std::string>>* tileData, const bool* vMap) {
        if (*vMap) {
            //create map object with player number and tiles
            Map* gameMap = new Map(*playerNumber, *tileData);
            return gameMap;
        }
        //there was an error, map was not created
        return nullptr;
    }

/**
 * Sets the map file to load
 * @param newMapFile, string of the map name
 */
void MapLoader::setMapFile(std::string newMapFile) {
    pMapFile = new std::string(std::move(newMapFile));
}

/**
 * Helper function that splits a map file's line by spaces
 * @param line, string map file line
 * @param pLineWords, pointer to a vector that holds the split up line
 */
void MapLoader::splitLine(const std::string& line, std::vector<std::string>* pLineWords) {
    //split each line into vector of words (split by spaces)
    std::istringstream iss(line);
    for (std::string s; iss >> s;) {
        pLineWords->push_back(s);
    }
}
    
/**
 * Helper function that checks if the current line holds the map name
 * @param playerNumber, pointer that holds the player number
 * @param lineWords, pointer to a vector that holds the split up line
 */
void MapLoader::getPlayerNumber(int* playerNumber, std::vector<std::string>* lineWords) {
    //get player number
    if (lineWords->at(0) == "players" || lineWords->at(0) == "Players") {
        for (unsigned long i = 1; i < lineWords->size(); i++) {
            *playerNumber = (*lineWords)[i] + " ";
        }
    }
}
    
/**
 * Helper function that checks if the current line specifies the start of a new section
 * @param mode, pointer string that holds the current map mode
 * @param lineWords, pointer to a vector that holds the split up line
 */
bool MapLoader::checkSection(std::string* mode, std::vector<std::string>* lineWords) {
    //separate in sections
    if ((*lineWords)[0][0] == *"[") {
        *mode = "";
        for (unsigned long i = 1; i < (*lineWords)[0].size() - 1; i++) {
            *mode += (*lineWords)[0][i];
        }
        return true;
    }
    return false;
}
    
bool validateTileLine(int* tileCount, std::vector<std::string>* lineWords, const int* lineCount, bool* validMap, bool verbose){
    (*tileCount)++;
    //check validity of the line in this mode
    if (lineWords->size() < 4) {
        if(verbose){
            std::cout << "Line " << *lineCount
                      << " - [ERROR] : a line in the tiles declaration had missing nodes, map could not be created.\n";
        }
        *validMap = false;
        return false;
    } else {
        if (lineWords->size() > 4 && verbose)
            std::cout << "Line " << *lineCount
                      << " - [WARNING] : a line in  the tiles declaration had extra nodes.\n";
    }
    else {
        return true;
    }
    
}

