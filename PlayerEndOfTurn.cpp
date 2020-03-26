#include <vector>
#include <iostream>
#include "GBMaps.h"
#include "VGMap.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "Player.h"
#include "Resources.h"
#include "Part6.h"


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