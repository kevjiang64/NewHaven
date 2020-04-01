#include <vector>
#include <iostream>
#include "GBMaps.h"
#include "VGMap.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "Player.h"
#include "Resources.h"
#include "Part6.h"

//Methods signature
static int askNbPlayers();
static Map* selectBoard(int nbPlayers);
static vector<Player*>* createPlayers(int nbPlayers);
static void assignVillageBoards(vector<Player*>* players, int nbPlayers);
static vector<Building>* drawBuildingsOnBoard(DeckBuilding* deckBuildings);

int main() {
	int nbPlayers = askNbPlayers();
	Map* board = selectBoard(nbPlayers);
	vector<Player*>* players = createPlayers(nbPlayers); 
	assignVillageBoards(players, nbPlayers);
	DeckHarvestTile* deckTiles = new DeckHarvestTile();
	DeckBuilding* deckBuildings = new DeckBuilding();
	vector<Building>* buildingsOnBoard = drawBuildingsOnBoard(deckBuildings);
	players->at(1)->displayState();
	return 0;
}

//Asks to the user and returns the nb of players wanted
static int askNbPlayers() {
	int nbPlayers;
	cout << "How many players do you want to play with? ";
	cin >> nbPlayers;
	while (!(nbPlayers == 2 || nbPlayers == 3 || nbPlayers == 4)) {
		cout << "Incorrect number of player. Please enter a number between 2 and 4" << endl;
		cout << "\nHow many players do you want to play with? ";
		cin >> nbPlayers;
	}
	return nbPlayers;
}

//Selects the right file from the GBMapsLoader depending on the nb of players
static Map* selectBoard(int nbPlayers) {
	//create an empty Map object
<<<<<<< HEAD
    Map* gameMap;

    //Depending on the number of players, run the setMapSize method from GBMaps to assign the correct ammount of nodes to the map
    //Prints out the correct game size
    if (nbPlayers == 2) {
        gameMap->setMapSize(2);
        gameMap->getMapSize(2);
    }
    else if (nbPlayers == 3) {
        gameMap->setMapSize(3);
        gameMap->getMapSize(3);
    }
    else if (nbPlayers == 4) {
        gameMap->setMapSize(4);
        gameMap->getMapSize(4);
    }
    return gameMap;
=======
	Map* gameMap;

	//Depending on the number of players, run the setMapSize method from GBMaps to assign the correct ammount of nodes to the map
	//Prints out the correct game size
	if (nbPlayers == 2) {
		gameMap->setMapSize(2);
		gameMap->getMapSize(2);
	}
	else if (nbPlayers == 3) {
		gameMap->setMapSize(3);
		gameMap->getMapSize(3);
	}
	else if (nbPlayers == 4) {
		gameMap->setMapSize(4);
		gameMap->getMapSize(4);
	}
	return gameMap;
>>>>>>> 0815ea6493fd5bb22bf79fd611e942393b3fd85c
}

static vector<Player*>* createPlayers(int nbPlayers) {
	vector<Player*>* players = new vector<Player*>(nbPlayers);
	for (int i = 0; i < nbPlayers; i++) {
		Player* player = new Player();
		(*players)[i] = player;
	}

	return players;
}

//Assign a village board from a file from the loader to each of the players
static void assignVillageBoards(vector<Player*>* players, int nbPlayers) {
	
	int row, col;
	string board;
	ifstream input("valid.txt");
	VGMap tempBoard1, tempBoard2, tempBoard3, tempBoard4;
	VGMap* playerBoard1, *playerBoard2, *playerBoard3, *playerBoard4;
	
	for (int i = 0; i < nbPlayers; i++)
	{
		//Check if the ifstream is still open
		if (fexists(input))
		{
			//Different name for each player
			if (i == 0)
			{
				board = checkValidName(input, "Milford");
				row = checkValidRow(input);
				col = checkValidRow(input);
				//Assigning and creating vg for each player
				tempBoard1 = VGMap(row, col, board);
				playerBoard1 = &tempBoard1;
				players->at(i)->setVillageBoard(playerBoard1);
			}
			if (i == 1)
			{
				board = checkValidName(input, "Guilford");
				row = checkValidRow(input);
				col = checkValidRow(input);
				//Assigning and creating vg for each player
				tempBoard2 = VGMap(row, col, board);
				playerBoard2 = &tempBoard2;
				players->at(i)->setVillageBoard(playerBoard2);
			}
			if (i == 2)
			{
				board = checkValidName(input, "Stratford");
				row = checkValidRow(input);
				col = checkValidRow(input);
				//Assigning and creating vg for each player
				tempBoard3 = VGMap(row, col, board);
				playerBoard3 = &tempBoard3;
				players->at(i)->setVillageBoard(playerBoard3);
			}
			if (i == 3)
			{
				board = checkValidName(input, "Fairfield");
				row = checkValidRow(input);
				col = checkValidRow(input);
				//Assigning and creating vg for each player
				tempBoard4 = VGMap(row, col, board);
				playerBoard4 = &tempBoard4;
				players->at(i)->setVillageBoard(playerBoard4);
			}
		}
	}
}
static vector<Building>* drawBuildingsOnBoard(DeckBuilding* deckBuildings) {
	vector<Building>* buildingsOnBoard = new vector<Building>(5);
	for (int i = 0; i < 5; i++) {
		(*buildingsOnBoard)[i] = deckBuildings->draw();
	}
	return buildingsOnBoard;
}
