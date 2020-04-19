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
#include "GameObservers.h"

using namespace std;


void gameTie(vector<Player*>* players);
vector<int>* fewestEmptySpaces(vector<Player*>* players, vector<bool>* tied);
vector<int>* leastBuildingsLeftOver(vector<Player*>* players, vector<bool>* tied);


