
#include <cstdlib>
#include <vector>

#include "Part6.h"
#include "GBMaps.h"
#include "VGMap.h"

using namespace std;

//Part 6 i

CountResources::CountResources() {

}

vector<int> CountResources::calculResourceMarkers(Map board, vector<Map::Node> nodesJustPlaced) {
	//nodesJustPlaced is an array in the right order of the 4 resources just placed on the board (they are the nodes on the actual board that corresponds to the current tile)
	vector<int> markersArray;
	for (int res = 0; res < 4; res++) { //for each of the resources
		bool resourceFound = false;

		int k = 0; //k: each of the four squares from the tile
		while (!resourceFound && k < 4) {
			if (*(nodesJustPlaced.at(k).getResourceType()) == res) {
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

int CountResources::recursiveCountResourceFromSquare(int res, Map::Node node) {
	int score = 1;
	node.setCounted(true);
	vector<Map::Node*>* adjacentNodes = node.getAdjNodes(); //returns an array of 4 values, either a node or null (or an empty node, depend on how the board is done) (but even if it's the side it should be an array of 4 things) else test? just cannot be undefined
	for (int i = 0; i < (*adjacentNodes).size(); i++) { //for all 4 values
		Map::Node* ptrTestedNode = (*adjacentNodes).at(i);
		if (!(*ptrTestedNode).getCounted() && ptrTestedNode != NULL && *((*ptrTestedNode).getResourceType()) == res) {
			score += recursiveCountResourceFromSquare(res, (*ptrTestedNode));
		}
	}
	node.setCounted(false);
	return score;
	//for all adjacent tiles, if same resource rappeler la methode avec cette tuile. Else return 1
}

int recursiveCountResourceFromSquare(int res, Map::Node node) {
	int score = 1;
	node.setCounted(true);
	vector<Map::Node*>* adjacentNodes = node.getAdjNodes(); //returns an array of 4 values, either a node or null (or an empty node, depend on how the board is done) (but even if it's the side it should be an array of 4 things) else test? just cannot be undefined
	for (int i = 0; i < 4; i++) { //for all 4 values
		if ((*adjacentNodes).at(i) != NULL && *((*(*adjacentNodes).at(i)).getResourceType()) == res) {
			score += recursiveCountResourceFromSquare(res, *((*adjacentNodes).at(i)));
		}
	}
	return score;
	//for all adjacent tiles, if same resource rappeler la methode avec cette tuile. Else return 1
}



Score::Score() {

}

int Score::countFinalPoints(VGMap villageBoard) {
	return villageBoard.countPoints();
}




