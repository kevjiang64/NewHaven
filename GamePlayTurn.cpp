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

//Method Signature
static void placeTile(Player* activePlayer, Map* board, DeckHarvestTile* deck);

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

//places a harvest tile on the board
static void placeTile(Player* activePlayer, Map* board, DeckHarvestTile* deck) {
	cout << "Here is the board: " << endl;
	board->display();
	cout << "Where do you want to place the tile? Please indicate the corresponding number." << endl;
	cout << "Row: ";
	int enteredRow;
	cin >> enteredRow;
	while (enteredRow < 1 || enteredRow > 7) {
		cout << "The row number is incorrect, please enter a number between 1 and 7: ";
		cin >> enteredRow;
	}
	cout << "Column: ";
	int enteredCol;
	cin >> enteredCol;
	while (enteredCol < 1 || enteredCol > 7) {
		cout << "The column number is incorrect, please enter a number between 1 and 7: ";
		cin >> enteredCol;
	}
	
	cout << "Here are the tile you possess: " << endl;
	activePlayer->getTiles().at(0).display();
	activePlayer->getTiles().at(1).display();
	if (!activePlayer->getShipmentTileUsed()) {
		cout << "You can also play your shipment tile" << endl;
	}

	cout << "Which tile do you want to place? (1 for your first tile, 2 for your second one, or 3 for your shipment tile) ";
	int enteredNumTile;
	cin >> enteredNumTile;
	while (!(enteredNumTile == 1 || enteredNumTile == 2 || enteredNumTile == 3)) {
		cout << "Invalid number!" << endl;
		cout << "Which tile do you want to place? (1 for your first tile, 2 for your second one, or 3 for your shipment tile) ";
		cin >> enteredNumTile;
	}

	cout << "Which corner do you want to place as the top left corner? (Please enter 1 for top left, 2 for top right, 3 for bottom right and 4 for bottom left) ";
	int enteredTopLeft;
	cin >> enteredTopLeft;
	while (!(enteredTopLeft == 1 || enteredTopLeft == 2 || enteredTopLeft == 3 || enteredTopLeft == 4)) {
		cout << "Invalid number!" << endl;
		cout << "Which corner do you want to place as the top left corner? (Please enter 1 for top left, 2 for top right, 3 for bottom right and 4 for bottom left) ";
		cin >> enteredTopLeft;
	}

	activePlayer->placeHarvestTile(enteredNumTile - 1, (enteredRow - 1) * 2, (enteredCol - 1) * 2, board, *deck, enteredTopLeft - 1);
}

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
	
	int done_building = 0, i = 0,game_finished = 0, share_index;

	//Continues to loop until one space left on the board
	while (!game_finished) 
	{
		for (int i = 0; i < nbPlayers; i++)
		{
			//Showing which player is playing
			cout << "Player with " << players->at(i)->getID() << " is now playing" << endl;

			//As long as they want to build
			while (!done_building)
			{
				string answer;

				//Player place building
				//players->at(i)->placeHarvestTile()
				buildPlayerVillage(*(players->at(i)));

				cout << "Do you want to build another building? (y/n): ";
				cin >> answer;

				//Not building anymore
				if (answer.compare("n") == 0)
					done_building = 1;
			}
			//Sharing the resources
			shareWealth(players, nbPlayers, i);
		}
	}
}

//Check if last player of the sequence 
static bool checkLastSequence(int index, int nbPlayer)
{
	return index == nbPlayer - 1;
}

//Letting other players use the rest of your resources
static void shareWealth(vector<Player*>* players,int nbPlayers,int index)
{
	int shared_index;
	string answer;

	//Check if last player of the sequence
	if (checkLastSequence(index, nbPlayers))
	{
		shared_index = 0;
	}
	else
	{
		shared_index = index + 1;
	}

	//Looping through every other player until reaching the same player
	while (players->at(shared_index)->getID() != players->at(index)->getID())
	{
		cout << "Transfering resources of the hand to the next player ==> ID : " << players->at(shared_index)->getID() << endl;
		transferResourceMarkers(players, index);

		//Next player
		if (checkLastSequence(index, nbPlayers))
		{
			index = 0;
		}
		else
		{
			index++;
		}
		//Asking if they want to build
		cout << "Do you want to build a building? (y/n): ";
		cin >> answer;
		
		//If yes to building
		while (answer.compare("y") == 0)
		{
			buildPlayerVillage(*(players->at(shared_index)));
			cout << "Do you want to build another building? (y/n): ";
			cin >> answer;
		}
		//Next player
		if (checkLastSequence(index, nbPlayers))
		{
			shared_index = 0;
		}
		else
		{
			shared_index++;
		}
	}
}

static void transferResourceMarkers(vector<Player*>* players, int i) {
	Hand prevHand = *players->at(i)->getHand();
	*(players->at(i + 1)->getHand()) = prevHand;
}

//Reordering the players in the actual vector based on their ID (lowest : at index 0 , highest : at n-1)
static void turnOrder(vector<Player*>* players, int nbPlayers)
{
	Player* tempPlayer;

	for (int i = 0; i < nbPlayers-1; i++)
	{
		for (int j = 0; j < nbPlayers - 1; j++)
		{
			//Next index ID smaller than current index ID
			if (players->at(j + 1)->getID() < players->at(j)->getID())
			{
				tempPlayer = players->at(j);
				players->at(j) = players->at(j + 1);
				players->at(j + 1) = tempPlayer;
			}
		}
	}
}