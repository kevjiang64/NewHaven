//
//  Player.cpp
//  Player
//
//  Created by Adèle Bédard on 2020-02-16.
//  Copyright © 2020 Adèle Bédard. All rights reserved.
//

#include "Player.h"
#include "Resources.h"
#include <vector>
#include "VGMap.h"
#include "GBMaps.h"
#include <iostream>
#include "Part6.h"
#include "GameObservers.h"
#include <random>
#include <list>

using namespace std;

Player::Player() {
	//Each player is assigned a random ID ranging from 1 to 100
    mt19937 rng;
    rng.seed(random_device()());
    uniform_int_distribution<mt19937::result_type> dist;
	
	id = new int(dist(rng) % 100 + 1);

	vb = new VGMap();

	buildings = new vector<Building*>;
	
	tiles = new vector<HarvestTile>;
	
	HarvestTile* tile1 = new HarvestTile();
	HarvestTile* tile2 = new HarvestTile();
	HarvestTile* shipmentTile = new HarvestTile();
	(*tiles).push_back(*tile1);
	(*tiles).push_back(*tile2);
	tiles->push_back(*shipmentTile);

	shipmentTileUsed = new bool(false);

	hand = new Hand();

	winner = new bool(false);
	
	_obs = new vector<vector<GameObserver*>*>();
	vector<GameObserver*>* _observersTile = new vector<GameObserver*>();
	vector<GameObserver*>* _observersBuild = new vector<GameObserver*>();
	vector<GameObserver*>* _observersEnd = new vector<GameObserver*>();
	_obs->push_back(_observersTile);
	_obs->push_back(_observersBuild);
	_obs->push_back(_observersEnd);
}

//Copy constructors of VillageBoard, Building and HarvestTile have to be defined
/*Player::Player(Player player) {
	*vb = new VGMap(player.(*vb));

	for (int i = 0; i < 6; i++) {
		(*buildings).insert(buildings.begin() + i, new Building(player.(*buildings).at(i)));
	}

	(*tiles)[0] = new HarvestTile(player.(*tiles)[0]);
	(*tiles)[1] = new HarvestTile(player.(*tiles)[1]);

	for (int i = 0; i < 4; i++) {
		(*resourceMarkers).push_back(player.(*resourceMarkers).at(i));
	}
}*/

Player::~Player() {
	delete vb;
	delete tiles;
	delete buildings;
	delete hand;
	delete shipmentTileUsed;
	delete id;

	vb = nullptr;
	tiles = nullptr;
	buildings = nullptr;
	hand = nullptr;
	shipmentTileUsed = nullptr;
	id = nullptr;
}

bool Player::placeHarvestTile(int noTile, int row, int col, Map* board, DeckHarvestTile deck, int topLeftCorner) {
	if (noTile == 0) {
		if (board->validPosition(row, col)) {
			tiles->at(0).setTopLeft(topLeftCorner);
			vector<Map::Node*> nodesJustPlaced = board->placeHarvestTile((*tiles).at(0), row, col);
			calculateResources(*board, false);
			drawHarvestTile(deck, 0);
			cout << "board: " << board->getMapNodes()->at(0)->getCol() << endl;
			notify(0);
			return true;
		}
		else {
			cout << "Not a valid position to place the tile" << endl;
			return false;
		}
	}
	else if (noTile == 1) {
		if (board->validPosition(row, col)) {
			tiles->at(1).setTopLeft(topLeftCorner);
			vector<Map::Node*> nodesJustPlaced = board->placeHarvestTile((*tiles).at(1), row, col);
			calculateResources(*board, false);
			drawHarvestTile(deck, 1);
			notify(0);
			return true;
		}
		else {
			cout << "Not a valid position to place the tile" << endl;
			return false;
		}
	}
	else if (noTile == 2) {
		if (*shipmentTileUsed) {
			cout << "Your shipment tile is no longer available" << endl;
			return false;
		}
		else {
			bool tilePlaced = placeShipmentTile(row, col, board, deck);
			return tilePlaced;
		}
	}
	else {
		cout << "Error with the tile number" << endl;
		return false;
	}
}

bool Player::placeShipmentTile(int row, int col, Map* board, DeckHarvestTile deck) {
	if (board->validPosition(row, col)) {
		cout << "You can have instances of a resource of your choice." << endl;
		cout << "Which resource do you choose? Please enter the number (1 - Meadow, 2 - Quarry, 3 - Forest or 4 - Wheatfield). ";
		int resourceEntered = 0;
		cin >> resourceEntered;
		while (!(resourceEntered == 1 || resourceEntered == 2 || resourceEntered == 3 || resourceEntered == 4)) {
			cout << "Please enter a number between 1 to 4 corresponding to the resource chosen." << endl;
			cout << "Which resource do you choose? Please enter the number (1 - Meadow, 2 - Quarry, 3 - Forest or 4 - Wheatfield). ";
			cin >> resourceEntered;
		}
		vector<int>* ressources = new vector<int>();
		for (int i = 0; i < 4; i++) {
			ressources->push_back(resourceEntered-1);
		}
		HarvestTile* newTile = new HarvestTile(ressources);
		vector<Map::Node*> nodesJustPlaced = board->placeHarvestTile(*newTile, row, col);
		
		cout << "You just placed your shipment tile!" << endl;
		calculateResources(*board, true);
		
		*shipmentTileUsed = true;
		cout << "Your shipment tile has been played and is no longer available." << endl;
		notify(0);
		return true;
	}
	else {
		cout << "Not a valid position to place the tile" << endl;
		return false;
	}
}

void Player::turnShipmentTile(Map* board) {
	if (board->lastTilePlacedIsShipmentTile()) {
		vector<int>* resourcesTile = tiles->at(2).getResources();
		vector<int*>* vectorResourcesTile = new vector<int*>();
		for (int i = 0; i < 4; i++) {
			int* theResource = new int(resourcesTile->at(i));
			vectorResourcesTile->push_back(theResource);
		}
		board->replaceResourcesShipmentTile(vectorResourcesTile);
	}
	
}

void Player::drawBuilding(DeckBuilding* deckBuilding) {
	Building* buildingDrawn = deckBuilding->draw();
	buildings->push_back(buildingDrawn);
}

void Player::drawHarvestTile(DeckHarvestTile deck, int no) {
	//create a harvest tile and put it in the empty spot
	//should I use the deck instead??
	if (no == 0) {
		HarvestTile tile = deck.draw();
		(*tiles)[0] = tile;
	} 
	else if (no == 1) {
		HarvestTile tile = deck.draw();
		(*tiles)[1] = tile;
	} 
	else {
		cout << "Error with the tile number";
	}
}

void Player::calculateResources(Map board, bool itIsTheShipmentTile) {
	CountResources* score = (new CountResources());
	vector<int> resources = score->calculResourceMarkers(board);
	hand->exchange(resources);
}



//outputs status of the resource markers
 void Player::resourceTracker() {
	 hand->printResources();
}



//Methods build and canBuild have to be implemented.
 bool Player::buildVillage(int buildingIndex, int row, int col) {
	 
	 Building* building = (*buildings).at(buildingIndex);
	 
	if ((*vb).canBuild(building, row, col)) { 
		(*vb).build(building, row, col);
		removeUsedResources(building);
		notify(1);
		return true;
	}
	else {
		cout << "Cannot build at this position, chose another one" << endl;
		return false;
	}
}

 void Player::removeUsedResources(Building* building)
 {
	 int buildingResource = building->getLabel();
	 int resourceAmount = building->getNumber();

	 hand->getResourceMarkers()->at(buildingResource) -= resourceAmount;

 }

 void Player::countPoints() {
	 vb->countPoints();
	 notify(2);
 }

 void Player::displayState() {
	 cout << "\nPlayer #" << *id << "\n" << endl;
	vb->displayVGmap();
	hand->printResources();
	cout << "" << endl;
	cout << "Harvest tiles: " << endl;
	for (int i = 0; i < 2; i++) {
		tiles->at(i).display();
	}
	if (*shipmentTileUsed) cout << "The shipment tile has been used." << endl;
	else cout << "The shipment tile has not been used." << endl;
	cout << "\nList of buildings: " << endl;
	for (int i = 0; i < buildings->size(); i++) {
		buildings->at(i)->display();
	}
 }

 void Player::resetResourceMarkers() {
	 hand->resetResourceMarkers();
 }



 //Subject
  void Player::attach(GameObserver* o, int noList)
 {
	  _obs->at(noList)->push_back(o);
 }

 void Player::detach(GameObserver* o, int noList)
 {
	 _obs->at(noList)->erase(std::remove(_obs->at(noList)->begin(), _obs->at(noList)->end(), o), _obs->at(noList)->end());
 }

 void Player::notify(int noList) 
 { 
	for (int i = 0; i < _obs->at(noList)->size(); i++) {
		_obs->at(noList)->at(i)->update();
	}
 }


