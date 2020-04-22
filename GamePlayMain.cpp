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
#include "GameEnd.h"
#include "GameObservers.h"


int main() {
	//gameStart
	int nbPlayers = askNbPlayers();
	Map* board = selectBoard(nbPlayers);
	DeckHarvestTile* deckTiles = new DeckHarvestTile(); 
	DeckBuilding* deckBuildings = new DeckBuilding(); 
	vector<Player*>* players = createPlayers(nbPlayers, deckBuildings);
	assignVillageBoards(players, nbPlayers);
	vector<Building*>* buildingsOnBoard = drawBuildingsOnBoard(deckBuildings); 
	displayAtGameStart(nbPlayers, players, board, buildingsOnBoard);
	
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
	gameTie(players);

	delete buildingsOnBoard;
	delete players;
	delete deckBuildings;
	delete deckTiles;
	delete board;

	return 0;
}
/**/