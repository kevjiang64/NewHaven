//
//  Player.cpp
//  Player
//
//  Created by Adèle Bédard on 2020-02-16.
//  Copyright © 2020 Adèle Bédard. All rights reserved.
//

#include "Player.h"
#include <vector>
#include "VGMap.h"
#include <iostream>

using namespace std;

Player::Player() {
	vb = new VGMap();

	for (int i = 0; i < 6; i++) {
		(*buildings).push_back(new Building());
	}

	(*tiles)[0] = new HarvestTile();
	(*tiles)[1] = new HarvestTile();

	for (int i = 0; i < 4; i++) {
		(*resourceMarkers).push_back(0);
	}
}

//Copy constructors of VillageBoard, Building and HarvestTile have to be defined
Player::Player(Player player) {
	*vb = new VillageBoard(player.(*vb));

	for (int i = 0; i < 6; i++) {
		(*buildings).insert(buildings.begin() + i, new Building(player.(*buildings).at(i)));
	}

	(*tiles)[0] = new HarvestTile(player.(*tiles)[0]);
	(*tiles)[1] = new HarvestTile(player.(*tiles)[1]);

	for (int i = 0; i < 4; i++) {
		(*resourceMarkers).push_back(player.(*resourceMarkers).at(i));
	}
}

Player::~Player() {
	delete[] vb;
	delete[] tiles;
	delete[] buildings;
	delete[] resourceMarkers;

	vb = NULL;
	tiles = NULL;
	buildings = NULL;
	resourceMarkers = NULL;
}

bool Player::placeHarvestTile(int noTile, Position pos, GameBoard board) {
	if (noTile == 0) {
		board.placeHarvestTile((*tiles).at(0), pos);
		drawHarvestTile(0);
		return true;
	}
	else if (noTile == 1) {
		board.placeHarvestTile((*tiles).at(1), pos);
		drawHarvestTile(1);
		return true;
	}
	else {
		cout << "Error with the tile number";
		return false;
	}
}

void Player::drawBuilding(DeckBuilding deckBuilding) {
	Building buildingDrawn = deckBuilding.draw();
	*buildings.push_back(buildingDrawn);
}

void Player::drawHarvestTile(int no) {
	//create a harvest tile and put it in the empty spot
	//should I use the deck instead??
	if (no == 0) {
		(*tiles)[0] = new HarvestTile();
	} 
	else if (no == 1) {
		(*tiles)[1] = new HarvestTile();
	} 
	else {
		cout << "Error with the tile number";
	}
}

void Player::calculateResources(Map board, Map::Node* nodesJustPlaced) {
	std::vector<int> resources = calculResourceMarkers(board, nodesJustPlaced);
	for (int i=0; i<4; i++) {
		(*resourceMarkers)[i] = resources.at(i);
	}
	cout << "Resources placed";
}


//ONE OR THE OTHER

//returns the pointer of resourceMarkers
std::vector<int>* Player::resourceTracker() {
	return resourceMarkers;
}

//returns the actual object
 std::vector<int> Player::resourceTracker() {
	return *resourceMarkers;
}

//outputs status of the resource markers
 void Player::resourceTracker() {
	cout << "Resources:\nName of resource 1:" << (*resourceMarkers).at(0) << "\nName of resource 2:" << (*resourceMarkers).at(1) << "\nName of resource 3:" << (*resourceMarkers).at(2) << "\nName of resource 4:" << (*resourceMarkers).at(3);
}



//Methods build and canBuild have to be implemented.
 bool buildVillage(int buildingIndex, VGMap::Node position) {
	Building building = (*buildings).at(buildingIndex);
	if ((*vb).canBuild(building, position) { //or canBuild(*vb, building, position) {
		*vb.build(building, position);
		return true;
	}
	else {
		cout << "Cannot build at this position, chose another one";
		return false;
	}
	*buildings.remove(*buildings.begin() + buildingIndex);
}

//maybe implement canBuild here
 //can also be done in the map itself, easier.

 bool canBuild(VGMap board, Building building, VGMap::Node pos) {
	bool canBuildNum = true;
	bool canBuildAdj = true;

	if (!building.isFlipped()) {
		//find out how to look for the number...
	}

	if (board.resourceAlreadyThere(building.resource)) {
		std::vector<VGMap::Node> adjacents = pos.getAdjacents();
		bool nodeFound = false;
		int in = 0;
		while (!nodeFound && in<4){
			if (adjacents.at(in).resource == building.resource) {
				nodeFound = true;
			} else {
				in++;
			}
		}
		if (nodeFound) {
			canBuildAdj = true;
		} else {
			canBuildAdj = false;
		}
	} 

	if (canBuildNum && canBuildAdj) {
		return true;
	} else {
		return false;
	}


	//For VGMap: add property resource already there.
}