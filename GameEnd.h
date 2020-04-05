#pragma once

#include <vector>
#include <iostream>
#include "GBMaps.h"
#include "VGMap.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "Player.h"
#include "Resources.h"
#include "Part6.h"

using namespace std;

void gameTie(Map* gameMap, vector<Player*>* players);
vector<int>* fewestEmptySpaces(vector<Player*>* players, vector<bool>* tied);
vector<int>* leastBuildingsLeftOver(vector<Player*>* players, vector<bool>* tied);
