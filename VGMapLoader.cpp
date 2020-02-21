//
//  VGMapLoader.cpp
//  COMP345_A1
//
//  Created by Justin Teixeira on 2020-02-21.
//  Copyright © 2020 Justin Teixeira. All rights reserved.
//

#include <stdio.h>
#include "GBMaps.h"
#include "VGMapLoader.h"
#include <sstream>
#include <algorithm>
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <iostream>


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
 * Sets the map file to load
 * @param newMapFile, string of the map name
 */
void MapLoader::setMapFile(std::string newMapFile) {
    pMapFile = new std::string(std::move(newMapFile));
}


