
#include <cstdlib>
#include <vector>

using namespace std;

//Part 6 i

public std::vector<int> calculResourceMarkers(GameBoard board, std::vector<GraphNode> nodesJustPlaced) { 
//nodesJustPlaced is an array in the right order of the 4 resources just placed on the board (they are the nodes on the actual board that corresponds to the current tile)
	std::vector<int> markersArray;
	for (int res=0; res<4; res++) { //for each of the resources
		boolean resourceFound = false;
		
		int k = 0; //k: each of the four squares from the tile
		while (!resourceFound && k < 4) {
			if (nodesJustPlaced.at(k).getResource() == res) {
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

private int recursiveCountResourceFromSquare(int res, GraphNode node) {
	int score = 1;
	node.counted = true;
	std::vector<GraphNode> adjacentNodes = node.getAdjacent(); //returns an array of 4 values, either a node or null (or an empty node, depend on how the board is done) (but even if it's the side it should be an array of 4 things) else test? just cannot be undefined
	for (int i = 0; i < 4; i++) { //for all 4 values
		if (adjacentNodes.at(i) != null && adjacentNodes.at(i).getResource() == res) {
			score += recursiveCountResourceFromSquare(res, adjacentNodes.at(i);
		}
	}
	return score;
	//for all adjacent tiles, if same resource rappeler la methode avec cette tuile. Else return 1
}





//Part 6 ii

public int countFinalPoints(VillageBoard villageBoard) {
	int score = 0;
	
	VGNode currentNode = nodeToStart; //would be cool if (0,0) : 1st column, number 6 (top)
	
	int i = 6;
	while (i>0) { //for each of the 6 rows
		bool doubled = true;
		int nbBuildingsCountedInRow = 0;

		if (currentNode.isEmpty()) { //skip to next non-empty row (for the first column):
			VGNode nextNodeCol = getNextNodeInColumn(currentNode);
			i--;
			while (nextNodeCol == NULL && i>1) { //find the first non empty row below
				nextNodeCol = getNextNodeInColumn(nextNodeCol);
				i--;
			}
			currentNode = nextNodeCol;
		}
		else {
			bool endOfRow = false;
			do {
				nbBuildingsCountedInRow++;
				if (currentNode.flipped) doubled = false;
				
				VGNode nextNodeRow = getNextNodeInRow(currentNode);

				if (nextNodeRow == NULL) {
					endOfRow = true;
					if (nbBuildingsCounted == 5) {
						if (doubled) score += 2 * currentNode.getNum();
						else score += currentNode.getNum();
					}
					
					bool beginningOfRow = false;
					do { //come back to beginning and go to next non empty row.
						VGNode prevNodeRow = getPrevNodeInRow(currentNode);
						if (prevNodeRow == NULL) {
							beginningOfRow = true;

							//go to next column
							if (i > 1) {
								VGNode nextNodeCol = getNextNodeInColumn(currentNode);
								i--;
								while (nextNodeCol == NULL && i>1) { //find the first non empty row below
									nextNodeCol = getNextNodeInColumn(nextNodeCol);
									i--;
								}
								currentNode = nextNodeCol;
							}
							
						}
						else {
							currentNode = prevNodeRow
						}
					} while (!beginningOfRow);
					
				}
				else {
					currentNode = nextNodeRow;
				}
			} while (!endOfRow);
			
			
			


			//iterate through the nodes and find the one that is not counted and of the same number
		}
	}
	
	//columns
	VGNode currentNode = nodeToStart; //would be cool if (0,0) : 1st column, number 6 (top)

	int i = 1;
	while (i < 6) { //for each of the 5 columns
		bool doubled = true;

		if (currentNode.isEmpty()) { //skip to next non-empty column (for the first row):
			VGNode nextNodeRow = getNextNodeInRow(currentNode);
			i--;
			while (nextNodeRow == NULL && i<5) { //find the first non empty row below
				nextNodeRow = getNextNodeInColumn(nextNodeRow);
				i++;
			}
			currentNode = nextNodeRow;
		}
		else {
			bool endOfColumn = false;
			do {
				if (currentNode.flipped) doubled = false;
				
				VGNode nextNodeCol = getNextNodeInCol(currentNode);

				if (nextNodeCol == NULL) {
					endOfColumn = true;

					if (currentNode.getNum() == 1) { //column complete: check score then go to next non-empty one
						if (doubled) score += 2 * (3 + abs(3 - currentNode.getNum()));
						else score += 3 + abs(3 - currentNode.getNum());
					}

					bool beginningOfCol = false;
					do { //come back to beginning and go to next non empty row.
						VGNode prevNodeCol = getPrevNodeInCol(currentNode);
						if (prevNodeCol == NULL) {
							beginningOfCol = true; //on est revenu au debut de la colonne

							if (i <5) { //go to next column
								VGNode nextNodeRow = getNextNodeInRow(currentNode);
								i++;
								while (nextNodeRow == NULL && i<5) { //find the first non empty columnon the right
									nextNodeRow = getNextNodeInRow(nextNodeRow);
									i++;
								}
								currentNode = nextNodeRow;
							}

						}
						else {
							currentNode = prevNodeCol
						}
					} while (!beginningOfCol);

				}
				else {
					currentNode = nextNodeCol;
				}
				
				
			} while (!endOfColumn);
		}

		
	}

	return score;

	//repeat:
	//go left
	//if blank or end, go to (1,0)
	//if turned double = false
	
	//then same with columns.

	// for sure we have to do all 6 rows.
	// for each row: is the first one empty, if so, go to next row directly. (find adjacent that has the inferior number)
	// if not: we have to traverse the row until either it's the end or it's not filled
	// if I do a method called find next adjacent or go to next adjacent. go to seems more intuitive. if it returns true, then continue and increment the counter. if it returns false it's done. when does the double thing change though?
	// if I do this all in one big function: first checks the first one. Then, iterates (while) and goes to the next one (checking for doubled) until it breaks. Then add points if count = 5. Then come back to next row, erasing every count made.
	// could i do submethods to find the next node wanted? it returns null if there is none.
}



private GraphNode getNextNodeInRow(GraphNode currentNode) {
	std::vector<VGNodes> adjacentNodes = currentNode.getAdjacentNodes();
	bool nodeFound = false;
	int index = 0;
	while (!nodeFound && index < 4) { //condition à revoir
		if (adjacentNodes.at(index) != NULL && adjacentNodes.at(index).getNum() == currentNode.getNum() && !adjacentNodes.at(index).hasBeenSeen()) {
			nodeFound = true;
			currentNode.setSeen(true);
		}
		else {
			index++; //attention! array index out of bound pourrait arriver
		}
	}
	if (nodeFound) return adjacentNodes[index];
	else return NULL;
}

private GraphNode getPrevtNodeInRow(GraphNode currentNode) {
	std::vector<VGNodes> adjacentNodes = currentNode.getAdjacentNodes();
	bool nodeFound = false;
	int index = 0;
	while (!nodeFound && index < 4 ) { //condition à revoir
		if (adjacentNodes.at(index)!= NULL && adjacentNodes.at(index).getNum() == currentNode.getNum() && adjacentNodes.at(index).hasBeenSeen()) {
			nodeFound = true;
			currentNode.setSeen(false);
		}
		else {
			index++; //attention! array index out of bound pourrait arriver
		}
	}
	if (nodeFound) return adjacentNodes[index];
	else return NULL;
}

private GraphNode getNextNodeInColumn(GraphNode currentNode) {
	std::vector<VGNodes> adjacentNodes = currentNode.getAdjacentNodes();
	bool nodeFound = false;
	int index = 0;
	while (!nodeFound && index < 4) { //condition à revoir
		if (adjacentNodes.at(index) != NULL && adjacentNodes.at(index).getNum() == currentNode.getNum() - 1) {
			nodeFound = true;
		}
		else {
			index++; //attention! array index out of bound pourrait arriver
		}
	}
	if (nodeFound) return adjacentNodes[index];
	else return NULL;
}

private GraphNode getPrevNodeInColumn(GraphNode currentNode) {
	std::vector<VGNodes> adjacentNodes = currentNode.getAdjacentNodes();
	bool nodeFound = false;
	int index = 0;
	while (!nodeFound && index < 4) { //condition à revoir
		if (adjacentNodes.at(index) != NULL && adjacentNodes.at(index).getNum() == currentNode.getNum() + 1) {
			nodeFound = true;
		}
		else {
			index++; //attention! array index out of bound pourrait arriver
		}
	}
	if (nodeFound) return adjacentNodes[index];
	else return NULL;
}

// I assume that it always gives me an array of 4 elements, please fill the array with null if it is not of length 4. 
//(still to do: figure out how null works in c++, maybe do a test main program)

//what is left to do:
//isEmpty() for the start element (or start at the first non empty and just drop the isEmpty part
//null: figure out how it works
//array with 4 (!!) elements, quitte a avoir des null
//make pointers what is pointers