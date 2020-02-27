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
