#include <vector>
#include <iostream>
#include "GBMaps.h"
#include "VGMap.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "Player.h"
#include "Resources.h"
#include "Part6.h"
#include "GamePlayTurn.h"

using namespace std;

//places a harvest tile on the board
void placeTile(Player* activePlayer, Map* board, DeckHarvestTile* deck) {
	cout << "\nHere is the board: " << endl;
	board->display();
	cout << "\nHere are the tile you possess: " << endl;
	activePlayer->getTiles()->at(0).display();
	activePlayer->getTiles()->at(1).display();
	if (!activePlayer->getShipmentTileUsed()) {
		cout << "You can also play your shipment tile" << endl;
	}
	cout << "" << endl;

	cout << "Which tile do you want to place? (1 for your first tile, 2 for your second one, or 3 for your shipment tile) ";
	int enteredNumTile;
	cin >> enteredNumTile;
	while (!(enteredNumTile == 1 || enteredNumTile == 2 || enteredNumTile == 3)) {
		cout << "Invalid number!" << endl;
		cout << "Which tile do you want to place? (1 for your first tile, 2 for your second one, or 3 for your shipment tile) ";
		cin >> enteredNumTile;
	}

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

	

	

	cout << "Which corner do you want to place as the top left corner? (Please enter 1 for top left, 2 for top right, 3 for bottom right and 4 for bottom left) ";
	int enteredTopLeft;
	cin >> enteredTopLeft;
	while (!(enteredTopLeft == 1 || enteredTopLeft == 2 || enteredTopLeft == 3 || enteredTopLeft == 4)) {
		cout << "Invalid number!" << endl;
		cout << "Which corner do you want to place as the top left corner? (Please enter 1 for top left, 2 for top right, 3 for bottom right and 4 for bottom left) ";
		cin >> enteredTopLeft;
	}
	
	bool tilePlaced = activePlayer->placeHarvestTile(enteredNumTile - 1, (enteredRow - 1) * 2, (enteredCol - 1) * 2, board, *deck, enteredTopLeft - 1);
	if (!tilePlaced) {
		cout << "Error! The tile cannot be placed, please try again!" << endl;
		placeTile(activePlayer, board, deck);
	}
	else {
		cout << "\nHere is the resulting board: " << endl;
		board->display();
	}
}

//Place a building in the VGMap board
void buildPlayerVillage(Player* player)
{
	int rowEntered, colEntered, indexEntered;
	string flippedEntered;
	bool result = false;

	//Checking what building and where to put it
	cout << "Which building do you want to place in board? (1-?)" << "\n";
	cin >> indexEntered;
	while (indexEntered < 1) {
		cout << "Error, incorrect index! Please try again." << endl;
		cout << "Which building do you want to place in board? (1-?)" << "\n";
		cin >> indexEntered;
	}
	int index = indexEntered - 1;

	cout << "On which row do you want to place the building? (1-6)" << "\n";
	cin >> rowEntered;
	while (rowEntered < 1 || rowEntered>6) {
		cout << "Error, incorrect row value! Please try again." << endl;
		cout << "On which row do you want to place the building? (1-6)" << "\n";
		cin >> rowEntered;
	}
	int row = 6 - rowEntered;

	cout << "On which column do you want to place the building? (1-5)" << "\n";
	cin >> colEntered;
	while (colEntered < 1 || colEntered>5) {
		cout << "Error, incorrect column value! Please try again." << endl;
		cout << "On which row do you want to place the building? (1-5)" << "\n";
		cin >> colEntered;
	}
	int col = colEntered - 1;

	cout << "Do you want to flip it? (y/n) ";
	cin >> flippedEntered;
	while (flippedEntered.compare("y") != 0 && flippedEntered.compare("n") != 0) {
		cout << "Error, invalid value! Please try again." << endl;
		cout << "Do you want to flip it? (y/n) ";
		cin >> flippedEntered;
	}
	bool flipped;
	if (flippedEntered.compare("y") == 0) {
		flipped = true;
	}
	else {
		flipped = false;
	}

	if (flipped) {
		//number of the building becomes row number entered
		player->getBuildings()->at(index)->setNumber(rowEntered);
		player->getBuildings()->at(index)->setFlipped(true);
	}

	//Checking if player has enough resources
	if (enoughResources(player,index))
	{
		//Method return true if the village is successfully put
		result = player->buildVillage(index, row, col);
	}
	else
	{
		cout << "Player can't doesn't have enough resources" << "\n";
	}
	//Reducing the number of resources of player's hand
	if (result)
	{
		removeUsedResources(player, index);
		vector<Building*>* buildings = player->getBuildings();
		buildings->erase(buildings->begin() + index);
	}
	//Showing player's new resources
	player->getHand()->printResources();
}

//Check if player has enough resources
bool enoughResources(Player* player,int index)
{
	//Type of resources
	int buildingResource = player->getBuildings()->at(index)->getLabel();
	//Number of resources
	int resourceAmount = player->getBuildings()->at(index)->getNumber();
	


	return (player->getHand()->getResourceMarkers()->at(buildingResource) >= resourceAmount);
}
//Remove used resources
void removeUsedResources(Player* player, int index)
{
	int buildingResource = player->getBuildings()->at(index)->getLabel();
	int resourceAmount = player->getBuildings()->at(index)->getNumber();

	player->getHand()->getResourceMarkers()->at(buildingResource) -= resourceAmount;
	
}

void endOfTurn(Player* activePlayer, vector<Building*>* buildingsOnBoard, DeckBuilding* deck, vector<Player*>* players) {
	endTurnDrawBuildings(activePlayer, buildingsOnBoard, deck);
	endTurnResetResourceMarkers(players);
	endTurnDrawNewBuildingsToBoard(buildingsOnBoard, deck);
	cout << "\nHere are your possessions at the end of your turn:" << endl;
	activePlayer->displayState();
}

void endTurnDrawBuildings(Player* activePlayer, vector<Building*>* buildingsOnBoard, DeckBuilding* deck) {
	cout << "\nPlayer #" << activePlayer->getID() << "," << endl;
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
			cout << "\nFor the next building to draw, do you want to draw it from the board or the deck? (1 for board, 2 for deck) ";
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
				Building* buildingDrawn = deck->draw();
				activePlayer->getBuildings()->push_back(buildingDrawn);
				cout << "\nBuilding drawn:\t";
				buildingDrawn->display();
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

void endTurnDrawBuildingFromBoard(Player* activePlayer, vector<Building*>* buildingsOnBoard) {
	cout << "Here are the buildings on the board: " << endl;
	for (int i = 0; i < buildingsOnBoard->size(); i++) {
		cout << i + 1 << " -\t";
		buildingsOnBoard->at(i)->display();
	}
	cout << "\nWhich one do you want to take? Please enter the corresponding number. ";
	int numEntered = 0;
	cin >> numEntered;
	while (numEntered<1 || numEntered > buildingsOnBoard->size()) {
		cout << "Error in entering your choice." << endl;
		cout << "Which one do you want to take? Please enter the corresponding number. ";
		cin >> numEntered;
	}
	Building* buildingChosen = buildingsOnBoard->at(numEntered - 1);
	activePlayer->getBuildings()->push_back(buildingChosen);
	buildingsOnBoard->erase(buildingsOnBoard->begin() + numEntered - 1); // will it erase the one in the player's hand too? test it
}

 void endTurnResetResourceMarkers(vector<Player*>* players) {
	for (int i = 0; i < players->size(); i++) {
		players->at(i)->resetResourceMarkers();
	}
}

void endTurnDrawNewBuildingsToBoard(vector<Building*>* buildingsOnBoard, DeckBuilding* deck) {
	for (int i = buildingsOnBoard->size(); i < 5; i++) {
		buildingsOnBoard->push_back(deck->draw());
	}
}

void turnSequence(vector<Player*>* players, int nbPlayers) {
	
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
				buildPlayerVillage((players->at(i)));

				cout << "Do you want to build another building? (y/n): ";
				cin >> answer;

				//Not building anymore
				if (answer.compare("n") == 0)
					done_building = 1;
			}
			//Sharing the resources
			shareWealth(players, nbPlayers, i);
			//endOfTurn(players->at(i),);
		}
	}
}

//Check if last player of the sequence 
bool checkLastSequence(int index, int nbPlayer)
{
	return index == nbPlayer - 1;
}

//Letting other players use the rest of your resources
void shareWealth(vector<Player*>* players,int nbPlayers,int index)
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
			buildPlayerVillage((players->at(shared_index)));
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

void buildingSequence(vector<Player*>* players, int nbPlayers, int index) {
	int i = 0;
	int indexPlayer = index;
	bool stillResources = true;
	while (i < nbPlayers && stillResources) { //pour chaque player
		Player* activePlayer = players->at(indexPlayer);
		//construire autant de building qu'il veut
		string answer;
		//Asking if they want to build
		if (!resourcesEmpty(activePlayer)) {
			cout << "\nPlayer #" << activePlayer->getID() << ":" << endl;
			cout << "\nHere are your buildings: " << endl;
			vector<Building*>* buildings = activePlayer->getBuildings();
			for (int i = 0; i < buildings->size(); i++) {
				cout << "Building #" << i + 1 << "\t";
				buildings->at(i)->display();
			}
			cout << "\nHere is your board: " << endl;
			activePlayer->getVillageBoard()->displayVGmap();

			cout << "\nDo you want to build a building? (y/n): ";
			cin >> answer;
			while (answer.compare("y") != 0 && answer.compare("n") != 0) {
				cout << "Error, invalid value! Please try again.";
				cout << "\nDo you want to build a building? (y/n): ";
				cin >> answer;
			}

			//If yes to building
			while (answer.compare("y") == 0 && !resourcesEmpty(activePlayer))
			{
				buildPlayerVillage(activePlayer);

				cout << "\nHere are your buildings: " << endl;
				vector<Building*>* buildings = activePlayer->getBuildings();
				for (int i = 0; i < buildings->size(); i++) {
					cout << "Building #" << i + 1 << "\t";
					buildings->at(i)->display();
				}
				cout << "\nHere is your board: " << endl;
				activePlayer->getVillageBoard()->displayVGmap();

				cout << "\nDo you want to build a building? (y/n): ";
				cin >> answer;
				while (answer.compare("y") != 0 && answer.compare("n") != 0) {
					cout << "Error, invalid value! Please try again.";
					cout << "\nDo you want to build a building? (y/n): ";
					cin >> answer;
				}
			}

			//transférer au suivant
			if (!resourcesEmpty(activePlayer)) {
				transferResourceMarkers(players, indexPlayer);

				indexPlayer++;
				if (indexPlayer == nbPlayers) {
					indexPlayer = 0;
				}
			}
			else {
				cout << "No more resources available" << endl;
				stillResources = false;
			}
			
		}
		else {
			cout << "No more resources available (shouldn't be happening at this point...)" << endl;
			stillResources = false;
		}
		i++;
		
	}

}

bool resourcesEmpty(Player* activePlayer) {
	vector<int>* resourceMarkers = activePlayer->getHand()->getResourceMarkers();
	bool isEmpty = true;
	int index = 0;
	while (isEmpty && index<4) {
		if (resourceMarkers->at(index) != 0) {
			isEmpty = false;
		}
		index++;
	}
	return isEmpty;
}
 
void transferResourceMarkers(vector<Player*>* players, int i) {
	Hand prevHand = *players->at(i)->getHand();
	if (i == players->size() - 1) {
		*(players->at(0)->getHand()) = prevHand;
	}
	else {
		*(players->at(i + 1)->getHand()) = prevHand;
	}
	
}

//Reordering the players in the actual vector based on their ID (lowest : at index 0 , highest : at n-1)
void turnOrder(vector<Player*>* players, int nbPlayers)
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