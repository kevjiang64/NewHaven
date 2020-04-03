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

int askNbPlayers();
Map* selectBoard(int nbPlayers);
vector<Player*>* createPlayers(int nbPlayers, DeckBuilding* deckBuildings);
void assignVillageBoards(vector<Player*>* players, int nbPlayers);
vector<Building*>* drawBuildingsOnBoard(DeckBuilding* deckBuildings);
void displayAtGameStart(int nbPlayers, vector<Player*>* players, Map* board);