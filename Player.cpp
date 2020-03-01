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

using namespace std;

Player::Player() {
	vb = new VGMap();

	buildings = new vector<Building>;

	for (int i = 0; i < 6; i++) {
		Building building;
		(*buildings).push_back(*(new Building()));
	}

	tiles = new vector<HarvestTile>;
	HarvestTile tile1;
	HarvestTile tile2;
	(*tiles).push_back(tile1);
	(*tiles).push_back(tile2);

	
	resourceMarkers = new vector<int>;

	for (int i = 0; i < 4; i++) {
		(*resourceMarkers).push_back(0);
	}
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

bool Player::placeHarvestTile(int noTile, Map board, DeckHarvestTile deck) {
	if (noTile == 0) {
		board.placeHarvestTile((*tiles).at(0));
		drawHarvestTile(deck, 0);
		return true;
	}
	else if (noTile == 1) {
		board.placeHarvestTile((*tiles).at(1));
		drawHarvestTile(deck, 1);
		return true;
	}
	else {
		cout << "Error with the tile number";
		return false;
	}
}

void Player::drawBuilding(DeckBuilding deckBuilding) {
	Building buildingDrawn = deckBuilding.draw();
	(*buildings).push_back(buildingDrawn);
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

void Player::calculateResources(Map board, vector<Map::Node> nodesJustPlaced) {
	CountResources score = *(new CountResources());
	std::vector<int> resources = score.calculResourceMarkers(board, nodesJustPlaced);
	for (int i=0; i<4; i++) {
		(*resourceMarkers)[i] = resources.at(i);
	}
	cout << "Resources placed";
}


//ONE OR THE OTHER

//returns the pointer of resourceMarkers
/*std::vector<int>* Player::resourceTracker() {
	return resourceMarkers;
}

//returns the actual object
 std::vector<int> Player::resourceTracker() {
	return *resourceMarkers;
}*/

//outputs status of the resource markers
 void Player::resourceTracker() {
	 
	 cout << "Resources:\nName of resource 1:" << (*resourceMarkers).at(0) << "\nName of resource 2:" << (*resourceMarkers).at(1) << "\nName of resource 3:" << (*resourceMarkers).at(2) << "\nName of resource 4:" << (*resourceMarkers).at(3);
}



//Methods build and canBuild have to be implemented.
 bool Player::buildVillage(int buildingIndex, int row, int col) {
	Building building = (*buildings).at(buildingIndex);
	if ((*vb).canBuild(building, row, col)) { //or canBuild(*vb, building, position) {
		(*vb).build(building, row, col);
		return true;
	}
	else {
		cout << "Cannot build at this position, chose another one";
		return false;
	}
	(*buildings).erase((*buildings).begin() + buildingIndex);
}


