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


/*int main() {
	//gameStart
	int nbPlayers = askNbPlayers();
	Map* board = selectBoard(nbPlayers);
	DeckHarvestTile* deckTiles = new DeckHarvestTile(); 
	DeckBuilding* deckBuildings = new DeckBuilding(); 
	vector<Player*>* players = createPlayers(nbPlayers, deckBuildings);
	assignVillageBoards(players, nbPlayers);
	vector<Building*>* buildingsOnBoard = drawBuildingsOnBoard(deckBuildings); 
	displayAtGameStart(nbPlayers, players, board, buildingsOnBoard);

	//turn sequence for the first player in the vector, for testing purposes
    // player with smallest ID will begin
	Player* activePlayer = players->at(checkFirstPlayer(players, nbPlayers));
	oneTurn(activePlayer, board, deckTiles, players, nbPlayers, buildingsOnBoard, deckBuildings);
	

	return 0;
}*/
