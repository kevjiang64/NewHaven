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


static int askNbPlayers();
static Map* selectBoard(int nbPlayers);
static vector<Player*>* createPlayers(int nbPlayers);
static void assignVillageBoards(vector<Player*>* players, int nbPlayers);
static vector<Building>* drawBuildingsOnBoard(DeckBuilding* deckBuildings);
static void displayAtGameStart(int nbPlayers, vector<Player*>* players, Map* board);