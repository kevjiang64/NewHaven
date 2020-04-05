#pragma once
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
#include "GBMaps.h"
#ifndef GBMapLoader_h
#define GBMapLoader_h

class GBMapLoader {
public:
    GBMapLoader(int numOfPlayers, std::vector<Map::Node*> initTile);
    //GBMaps getTestMap() { return *testMap; };
private:
    //GBMaps* testMap;
};

bool checkFile(string fileName);
int checkValidPlayerNum(string fileName);
std::vector<Map::Node*>* checkValidTile(string fileName);
void placeTilesFromLoader(string fileName, Map* board);
#endif /* GBMapLoader_h */