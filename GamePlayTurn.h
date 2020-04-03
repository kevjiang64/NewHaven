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

void placeTile(Player* activePlayer, Map* board, DeckHarvestTile* deck);

void buildPlayerVillage(Player* player);
bool enoughResources(Player* player, int index);
void removeUsedResources(Player* player, int index);

void endOfTurn(Player* activePlayer, vector<Building*>* buildingsOnBoard, DeckBuilding* deck, vector<Player*>* players);
void endTurnDrawBuildings(Player* activePlayer, vector<Building*>* buildingsOnBoard, DeckBuilding* deck);
void endTurnDrawBuildingFromBoard(Player* activePlayer, vector<Building*>* buildingsOnBoard);
void endTurnResetResourceMarkers(vector<Player*>* players);
void endTurnDrawNewBuildingsToBoard(vector<Building*>* buildingsOnBoard, DeckBuilding* deck);

void turnSequence(vector<Player*>* players, int nbPlayers);
void transferResourceMarkers(vector<Player*>* players, int i);
void shareWealth(vector<Player*>* players, int nbPlayers, int index);

void buildingSequence(vector<Player*>* players, int nbPlayers, int index);
bool resourcesEmpty(Player* activePlayer);