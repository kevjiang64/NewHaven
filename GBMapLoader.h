//
//  GBMapLoader.h
//  COMP345_A1
//
//  Created by Justin Teixeira on 2020-02-10.
//  Copyright © 2020 Justin Teixeira. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <iostream>
#include "Map.h"
#ifndef GBMapLoader_h
#define GBMapLoader_h

class MapLoader {
public:
    explicit MapLoader(std::string mapFile = "");
    virtual ~MapLoader();
    MapLoader(const MapLoader& toCopy);
    void operator=(MapLoader& rhs);
    std::string* pMapFile;
    void setMapFile(std::string newMapFile);
    virtual Map* readMapFile();

private:
    static Map* initMapObject(int* playerNumber, std::vector<std::vector<std::string>>* nodes, const bool* vMap);
    void splitLine(const std::string& line, std::vector<std::string>* pLineWords);
    bool checkSection(std::string* mode, std::vector<std::string>* lineWords);
    bool validateContinentLine(int* continentCount, std::vector<std::string>* lineWords, const int* lineCount,
                               bool* validMap,bool verbose);
    bool validateCountryLine(int* countryCount, std::vector<std::string>* lineWords, const int* lineCount, bool* validMap,
                        int* countryID, const int* continentCount,bool verbose);
    bool validateBordersLine(std::vector<int>* lineNums, std::vector<std::string>* lineWords, const int* lineCount,
                             bool* validMap, const int* countryCount,bool verbose);
};
