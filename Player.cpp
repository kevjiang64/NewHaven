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

bool Player::placeHarvestTile(int noTile, int row, int col, Map board, DeckHarvestTile deck) {
	if (noTile == 0) {
		
		if (board.validPosition(row, col)) {
			vector<Map::Node> nodesJustPlaced = board.placeHarvestTile((*tiles).at(0), row, col);
			calculateResources(board, nodesJustPlaced);
			drawHarvestTile(deck, 0);
			return true;
		}
		else {
			cout << "Not a valid position to place the tile" << endl;
			return false;
		}
	}
	else if (noTile == 1) {
		if (board.validPosition(row, col)) {
			board.placeHarvestTile((*tiles).at(1), row, col);
			drawHarvestTile(deck, 1);
			return true;
		}
		else {
			cout << "Not a valid position to place the tile" << endl;
			return false;
		}
	}
	else {
		cout << "Error with the tile number" << endl;
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
	hand->exchange(resources);
	
	cout << "Resources placed" << endl;
}



//outputs status of the resource markers
 void Player::resourceTracker() {
	 hand->printResources();
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


