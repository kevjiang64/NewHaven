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

using namespace std;

Player::Player() {
	VGMap* villageBoard = new VGMap();
	vb = villageBoard;

	vector<Building> builds;
	*buildings = builds;

	for (int i = 0; i < 6; i++) {
		Building building;
		(*buildings).push_back(building);
	}

	HarvestTile tile1;
	HarvestTile tile2;
	(*tiles)[0] = tile1;
	(*tiles)[1] = tile2;

	vector<int> resources;
	*resourceMarkers = resources;

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
	delete[] vb;
	delete[] tiles;
	delete[] buildings;
	delete[] resourceMarkers;

	vb = NULL;
	tiles = NULL;
	buildings = NULL;
	resourceMarkers = NULL;
}

/*bool Player::placeHarvestTile(int noTile, Map::Node pos, Map board) {
	if (noTile == 0) {
		board.placeHarvestTile((*tiles).at(0), pos);
		drawHarvestTile();
		return true;
	}
	else if (noTile == 1) {
		board.placeHarvestTile((*tiles).at(1), pos);
		drawHarvestTile();
		return true;
	}
	else {
		cout << "Error with the tile number";
		return false;
	}
}*/

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

/*void Player::calculateResources(Map board, vector<Map::Node> nodesJustPlaced) {
	
	std::vector<int> resources = calculResourceMarkers(board, nodesJustPlaced);
	for (int i=0; i<4; i++) {
		(*resourceMarkers)[i] = resources.at(i);
	}
	cout << "Resources placed";
}*/


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
/* bool Player::buildVillage(int buildingIndex, VGMap::Node node) {
	Building building = (*buildings).at(buildingIndex);
	if ((*vb).canBuild(building, node)) { //or canBuild(*vb, building, position) {
		(*vb).build(building, node);
		return true;
	}
	else {
		cout << "Cannot build at this position, chose another one";
		return false;
	}
	(*buildings).erase((*buildings).begin() + buildingIndex);
}*/

//maybe implement canBuild here
 //can also be done in the map itself, easier.

 /*bool canBuild(VGMap board, Building building, VGMap::Node pos) {
	 bool canBuildNum = true;
	 bool canBuildAdj = true;

	 if (!building.isFlipped()) {
		 //find out how to look for the number...
	 }

	 if (board.resourceAlreadyThere(building.getResource())) {
		 std::vector<VGMap::Node> adjacents = pos.getAdjacents();
		 bool nodeFound = false;
		 int in = 0;
		 while (!nodeFound && in < 4) {
			 if (adjacents.at(in).resource == building.resource) {
				 nodeFound = true;
			 }
			 else {
				 in++;
			 }
		 }
		 if (nodeFound) {
			 canBuildAdj = true;
		 }
		 else {
			 canBuildAdj = false;
		 }
	 }

	 if (canBuildNum && canBuildAdj) {
		 return true;
	 }
	 else {
		 return false;
	 }


	 //For VGMap: add property resource already there.
 }*/

 //part 6 i.
 vector<int> Player::calculResourceMarkers(Map board, vector<Map::Node> nodesJustPlaced) {
	 //nodesJustPlaced is an array in the right order of the 4 resources just placed on the board (they are the nodes on the actual board that corresponds to the current tile)
	 vector<int> markersArray;
	 for (int res = 0; res < 4; res++) { //for each of the resources
		 bool resourceFound = false;

		 int k = 0; //k: each of the four squares from the tile
		 while (!resourceFound && k < 4) {
			 if (nodesJustPlaced.at(k).getResourceType() == res) {
				 resourceFound = true;
				 //we found the place where the resource is on the tile, now we check adjacency
				 //add a propriety to each square: counted that is reinitialized after each count of this method


				 markersArray[res] = recursiveCountResourceFromSquare(res, nodesJustPlaced.at(k));

			 }
			 k++;
		 }
	 }
	 return markersArray;
 }

int Player::recursiveCountResourceFromSquare(int res, Map::Node node) {
	 int score = 1;
	 node.setCounted(true);
	 vector<Map::Node*>* adjacentNodes = node.getAdjNodes(); //returns an array of 4 values, either a node or null (or an empty node, depend on how the board is done) (but even if it's the side it should be an array of 4 things) else test? just cannot be undefined
	 for (int i = 0; i < (*adjacentNodes).size(); i++) { //for all 4 values
		 Map::Node* ptrTestedNode = (*adjacentNodes).at(i);
		 if (!(*ptrTestedNode).getCounted() && ptrTestedNode != NULL && (*ptrTestedNode).getResourceType() == res) {
			 score += recursiveCountResourceFromSquare(res, (*ptrTestedNode));
		 }
	 }
	 node.setCounted(false);
	 return score;
	 //for all adjacent tiles, if same resource rappeler la methode avec cette tuile. Else return 1
}

int main() {
	cout << "hello" << endl;
	return 0;
}