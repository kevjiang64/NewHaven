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
	vector<Building*>* buildingsOnBoard = drawBuildingsOnBoard(deckBuildings); //Don't Understand ? + where does each player draw 6 building tiles and 2 harvest tiles
	displayAtGameStart(nbPlayers, players, board);

	//turn sequence for the first player in the vector, for testing purposes
	// player with smallest ID will begin
	cout << "\n\nThe game starts" << endl;
	int indexActivePlayer = checkFirstPlayer(players, nbPlayers);
	
	while (!board->oneTileLeft()) {
		
		oneTurn(indexActivePlayer, board, deckTiles, players, nbPlayers, buildingsOnBoard, deckBuildings);

		indexActivePlayer++;
		if (indexActivePlayer == nbPlayers) {
			indexActivePlayer = 0;
		}
	}
	
	


	return 0;
}