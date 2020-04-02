#include <vector>
#include <iostream>
#include "GBMaps.h"
#include "VGMap.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "Player.h"
#include "Resources.h"
#include "Part6.h"

//Method Signature
void buildPlayerVillage(Player& player);
bool enoughResources(Player& player, int index);
void removeUsedResources(Player& player,int index);

static void endOfTurn(Player* activePlayer, vector<Building>* buildingsOnBoard, DeckBuilding* deck, vector<Player*>* players);
static void endTurnDrawBuildings(Player* activePlayer, vector<Building>* buildingsOnBoard, DeckBuilding* deck);
static void endTurnDrawBuildingFromBoard(Player* activePlayer, vector<Building>* buildingsOnBoard);
static void endTurnResetResourceMarkers(vector<Player*>* players);
static void endTurnDrawNewBuildingsToBoard(vector<Building>* buildingsOnBoard, DeckBuilding* deck);

static void turnSequence(vector<Player*>* players, int nbPlayers);
static void transferResourceMarkers(vector<Player*>* players, int i);


//Place a building in the VGMap board
void buildPlayerVillage(Player& player)
{
	int row, col, index;
	bool result = false;

	//Checking what building and where to put it
	cout << "Which building do you want to place in board? (0-?)" << "\n";
	cin >> index;
	cout << "On which row do you want to place the building? (0-5)" << "\n";
	cin >> row;
	cout << "On which column do you want to place the building? (0-5)" << "\n";
	cin >> col;

	//Showing player's resources
	player.getHand()->printResources();

	//Checking if player has enough resources
	if (enoughResources(player,index))
	{
		//Method return true if the village is successfully put
		result = player.buildVillage(index, row, col);
	}
	else
	{
		cout << "Player can't doesn't have enough resources" << "\n";
	}
	//Reducing the number of resources of player's hand
	if (result)
	{
		removeUsedResources(player, index);
	}
	//Showing player's new resources
	player.getHand()->printResources();
}

//Check if player has enough resources
bool enoughResources(Player& player,int index)
{
	//Type of resources
	int buildingResource = player.getBuildings().at(index).getLabel();
	//Number of resources
	int resourceAmount = player.getBuildings().at(index).getNumber();

	return (player.getHand()->getResourceMarkers()->at(buildingResource) > resourceAmount);
}
//Remove used resources
void removeUsedResources(Player& player, int index)
{
	int buildingResource = player.getBuildings().at(index).getLabel();
	int resourceAmount = player.getBuildings().at(index).getNumber();

	player.getHand()->getResourceMarkers()->at(buildingResource) -= resourceAmount;
}

static void endOfTurn(Player* activePlayer, vector<Building>* buildingsOnBoard, DeckBuilding* deck, vector<Player*>* players) {
	endTurnDrawBuildings(activePlayer, buildingsOnBoard, deck);
	endTurnResetResourceMarkers(players);
	endTurnDrawNewBuildingsToBoard(buildingsOnBoard, deck);
}

static void endTurnDrawBuildings(Player* activePlayer, vector<Building>* buildingsOnBoard, DeckBuilding* deck) {
	cout << "You can now draw new buildings for each empty resource." << endl;
	int countBuildingsToDraw = 0;
	for (int i = 0; i < 4; i++) {
		if (activePlayer->getHand()->getResourceMarkers()->at(i) == 0) {
			countBuildingsToDraw++;
		}
	}
	if (countBuildingsToDraw > 0) {
		endTurnDrawBuildingFromBoard(activePlayer, buildingsOnBoard);
		countBuildingsToDraw--;
		while (countBuildingsToDraw > 0) {
			cout << "For the next building to draw, do you want to draw it from the board or the deck? (1 for board, 2 for deck) ";
			int boardOrDeck = 0;
			cin >> boardOrDeck;
			while (!(boardOrDeck == 1 || boardOrDeck == 2)) {
				cout << "Error, invalid answer. Please try again:" << endl;
				cout << "For the next building to draw, do you want to draw it from the board or the deck? (1 for board, 2 for deck) ";
				cin >> boardOrDeck;
			}
			if (boardOrDeck == 1) {
				endTurnDrawBuildingFromBoard(activePlayer, buildingsOnBoard);
				countBuildingsToDraw--;
			}
			else if (boardOrDeck == 2) {
				activePlayer->getBuildings().push_back(deck->draw());
				countBuildingsToDraw--;
			}
			else {
				cout << "Error! Invalid behavior of method endTurnDrawBuildings() " << endl;
			}
		}
	}
	else {
		cout << "Error! Invalid behavior of method endTurnDrawBuildings() " << endl;
	}
}

static void endTurnDrawBuildingFromBoard(Player* activePlayer, vector<Building>* buildingsOnBoard) {
	cout << "Here are the buildings on the board: " << endl;
	for (int i = 0; i < buildingsOnBoard->size(); i++) {
		cout << i + 1 << " - ";
		//buildingsOnBoard->at(i).display();
	}
	cout << "Which one do you want to take? Please enter the corresponding number. ";
	int numEntered = 0;
	cin >> numEntered;
	while (!(numEntered == 1 || numEntered == 2 || numEntered == 3 || numEntered == 4 || numEntered == 5)) {
		cout << "Error in entering your choice." << endl;
		cout << "Which one do you want to take? Please enter the corresponding number. ";
		cin >> numEntered;
	}
	Building buildingChosen = buildingsOnBoard->at(numEntered - 1);
	activePlayer->getBuildings().push_back(buildingChosen);
	buildingsOnBoard->erase(buildingsOnBoard->begin() + numEntered - 1); // will it erase the one in the player's hand too? test it
}

static void endTurnResetResourceMarkers(vector<Player*>* players) {
	for (int i = 0; i < players->size(); i++) {
		players->at(i)->resetResourceMarkers();
	}
}

static void endTurnDrawNewBuildingsToBoard(vector<Building>* buildingsOnBoard, DeckBuilding* deck) {
	for (int i = buildingsOnBoard->size(); i < 5; i++) {
		buildingsOnBoard->push_back(deck->draw());
	}
}

static void turnSequence(vector<Player*>* players, int nbPlayers) {
	int done = 0;
	int i = 0;

	while (i < nbPlayers) {
		cout << "player " << /*players->at(i).id <<*/ " is now playing" << endl;

		while (!done) {
			string ans;

			//player place building
			buildPlayerVillage(*(players->at(i)));

			cout << "Do you want to build another building? (y/n): ";
			cin >> ans;

			if (ans == "n")
				done = 1;
		}

		cout << "transfering hand to the next player" << endl;
		transferResourceMarkers(players, i);
		i++;
	}
}

static void transferResourceMarkers(vector<Player*>* players, int i) {
	Hand prevHand = *players->at(i)->getHand();
	*(players->at(i + 1)->getHand()) = prevHand;
}