#include <cstdlib>
#include <vector>

#include "Part6.h"
#include "GBMaps.h"
#include "VGMap.h"
#include "Player.h"
#include "Resources.h"

using namespace std;

//Part 6 i

CountResources::CountResources() {

}

vector<int> CountResources::calculResourceMarkers(Map board) {
	//nodesJustPlaced is an array in the right order of the 4 resources just placed on the board (they are the nodes on the actual board that corresponds to the current tile)
	vector<int> markersArray = *(new vector<int>);
	for (int i = 0; i < 4; i++) {
		markersArray.push_back(0);
	}
	for (int res = 0; res < 4; res++) { //for each of the resources
		bool resourceFound = false;

		int k = 0; //k: each of the four squares from the tile
		while (!resourceFound && k < 4) {
			if (*(board.getMapNodes()->at(board.getMapNodes()->size() - k - 1)->getResourceType()) == res) {
				resourceFound = true;
				//we found the place where the first instance of the resource is on the tile, now we check adjacency

				markersArray[res] = recursiveCountResourceFromSquare(res, board.getMapNodes()->at(board.getMapNodes()->size() - k - 1));
				
				if (k == 0) {
					if ((board.getMapNodes()->at(board.getMapNodes()->size() - k - 3)) != nullptr && *(board.getMapNodes()->at(board.getMapNodes()->size() - k - 3)->getResourceType()) == res && *(board.getMapNodes()->at(board.getMapNodes()->size() - k - 2)->getResourceType()) != res && *(board.getMapNodes()->at(board.getMapNodes()->size() - k - 4)->getResourceType()) != res) {
						
						markersArray[res] += recursiveCountResourceFromSquare(res, board.getMapNodes()->at(board.getMapNodes()->size() - k - 3));
					}
				}
				else if (k == 1 ) {
					if ((board.getMapNodes()->at(board.getMapNodes()->size() - k - 3)) != nullptr && *(board.getMapNodes()->at(board.getMapNodes()->size() - k - 3)->getResourceType()) == res && *(board.getMapNodes()->at(board.getMapNodes()->size() - k - 2)->getResourceType()) != res && *(board.getMapNodes()->at(board.getMapNodes()->size() - k )->getResourceType()) != res) {
						
						markersArray[res] += recursiveCountResourceFromSquare(res, board.getMapNodes()->at(board.getMapNodes()->size() - k - 3));
					}
				}
				
				
			}
			k++;
		}
	}
	return markersArray;
}

int CountResources::recursiveCountResourceFromSquare(int res, Map::Node* node) {
	int score = 1;
	(*node).setCounted(true);
	
	vector<Map::Node*>* adjacentNodes = new vector<Map::Node*>();
	adjacentNodes = (*node).getAdjNodes(); //returns an array of 4 values, either a node or null (or an empty node, depend on how the board is done) (but even if it's the side it should be an array of 4 things) else test? just cannot be undefined
	for (int i = 0; i < (*adjacentNodes).size(); i++) { //for all 4 values
		
		Map::Node* ptrTestedNode = (*adjacentNodes).at(i);
		
		
		if (ptrTestedNode != nullptr && !(*ptrTestedNode).getCounted() && *((*ptrTestedNode).getResourceType()) == res) {
			score += recursiveCountResourceFromSquare(res, ptrTestedNode);
		}
	}
	
	(*node).setCounted(false);
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




