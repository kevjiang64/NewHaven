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

static void placeTile(Player* activePlayer, Map* board, DeckHarvestTile* deck);

void buildPlayerVillage(Player& player);
bool enoughResources(Player& player, int index);
void removeUsedResources(Player& player, int index);

static void endOfTurn(Player* activePlayer, vector<Building>* buildingsOnBoard, DeckBuilding* deck, vector<Player*>* players);
static void endTurnDrawBuildings(Player* activePlayer, vector<Building>* buildingsOnBoard, DeckBuilding* deck);
static void endTurnDrawBuildingFromBoard(Player* activePlayer, vector<Building>* buildingsOnBoard);
static void endTurnResetResourceMarkers(vector<Player*>* players);
static void endTurnDrawNewBuildingsToBoard(vector<Building>* buildingsOnBoard, DeckBuilding* deck);

static void turnSequence(vector<Player*>* players, int nbPlayers);
static void transferResourceMarkers(vector<Player*>* players, int i);
static void shareWealth(vector<Player*>* players, int nbPlayers, int index);