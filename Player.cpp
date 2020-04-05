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
#include <random>

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
	HarvestTile tile1;
	HarvestTile tile2;
	HarvestTile shipmentTile;
	(*tiles).push_back(tile1);
	(*tiles).push_back(tile2);
	tiles->push_back(shipmentTile);

	shipmentTileUsed = new bool(false);

	hand = new Hand();
	
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
	//delete[] vb;
	//delete[] tiles;
	//delete[] buildings;
	//delete[] resourceMarkers;

	//vb = NULL;
	//tiles = NULL;
	//buildings = NULL;
	//resourceMarkers = NULL;
}

bool Player::placeHarvestTile(int noTile, int row, int col, Map* board, DeckHarvestTile deck, int topLeftCorner) {
	if (noTile == 0) {
		if (board->validPosition(row, col)) {
			tiles->at(0).setTopLeft(topLeftCorner);
			vector<Map::Node*> nodesJustPlaced = board->placeHarvestTile((*tiles).at(0), row, col);
			calculateResources(*board);
			drawHarvestTile(deck, 0);
			cout << "board: " << board->getMapNodes()->at(0)->getCol() << endl;
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
			calculateResources(*board);
			drawHarvestTile(deck, 1);
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
		vector<Map::Node*> nodesJustPlaced = board->placeHarvestTile((*tiles).at(1), row, col);
		
		cout << "You just placed your shipment tile!" << endl;
		cout << "You can have four instances of a resource of your choice." << endl;
		cout << "Which resource do you choose? Please enter the number (1 - Meadow, 2 - Quarry, 3 - Forest or 4 - Wheatfield). ";
		int resourceEntered = 0;
		cin >> resourceEntered;
		while (!(resourceEntered == 1 || resourceEntered == 2 || resourceEntered == 3 || resourceEntered == 4)) {
			cout << "Please enter a number between 1 to 4 corresponding to the resource chosen." << endl;
			cout << "Which resource do you choose? Please enter the number (1 - Meadow, 2 - Quarry, 3 - Forest or 4 - Wheatfield). ";
			cin >> resourceEntered;
		}
		vector<int>* resources = new vector<int>(4);
		for (int i = 0; i < 4; i++) {
			if (i + 1 == resourceEntered) {
				resources->at(i) = 4;
			}
			else {
				resources->at(i) = 0;
			}
		}
		hand->exchange(*resources);
		*shipmentTileUsed = true;
		cout << "Your shipment tile has been played and is no longer available." << endl;
		return true;
	}
	else {
		cout << "Not a valid position to place the tile" << endl;
		return false;
	}
}

void Player::drawBuilding(DeckBuilding deckBuilding) {
	Building* buildingDrawn = deckBuilding.draw();
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

void Player::calculateResources(Map board) {
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
		return true;
	}
	else {
		cout << "Cannot build at this position, chose another one" << endl;
		return false;
	}
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
