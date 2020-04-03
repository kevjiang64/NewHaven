#include <vector>
#include <iostream>
#include "GBMaps.h"
#include "VGMap.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "Player.h"
#include "Resources.h"
#include "Part6.h"
#include "GameStart.h"
#include "GamePlayTurn.h"


int main() {
	//gameStart
	int nbPlayers = askNbPlayers();
	Map* board = selectBoard(nbPlayers);
	DeckHarvestTile* deckTiles = new DeckHarvestTile(); //Deck of Tiles not created ==> only count = 60
	DeckBuilding* deckBuildings = new DeckBuilding(); //Same ?
	vector<Player*>* players = createPlayers(nbPlayers, deckBuildings);
	assignVillageBoards(players, nbPlayers);
	vector<Building>* buildingsOnBoard = drawBuildingsOnBoard(deckBuildings); //Don't Understand ? + where does each player draw 6 building tiles and 2 harvest tiles
	displayAtGameStart(nbPlayers, players, board);

	//turn sequence for the first player in the vector, for testing purposes
	Player* activePlayer = players->at(0);
	activePlayer->displayState();
	placeTile(activePlayer, board, deckTiles);
	activePlayer->getHand()->printResources();
	buildingSequence(players, nbPlayers, 0);
	endOfTurn(activePlayer, buildingsOnBoard, deckBuildings, players);

	return 0;
}