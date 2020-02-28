#include "VGMap.h"
#include "Resources.h"
#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

//VGMap Constructor (Made for testing)
VGMap::VGMap(int row, int col)
{
	//Create 2D vector of 30 Nodes
	//(0,0) is at the top left	
	if(row == 6 && col == 5)
	{
		cout << "The inputed values for the rows and columns will create a 5x6 VGMap";
		for (int i = row; i < row; i++) 
		{
			vector<Node> column(col);
			(*board)[i] = column;
		}
		*points = 0;
	}
	else
	{
		cout << "The inputed values for the rows and columns will create a 5x6 VGMap";
	}
};
//VgMap Default Constructor 
VGMap::VGMap()
{
	//Create 2D vector of 30 Nodes
	//(0,0) is at the top left	
	for (int i = 0; i < 6; i++)
	{
		vector<Node> column(5);
		(*board)[i] = column;
	}
	*points = 0;
};

//Fill the board
//Clockwise => 0 : left , 1 : up, 2 : right, 3 : down
vector<VGMap::Node> VGMap::Node::fillAdjNodes(vector <vector<VGMap::Node>> board) {

	//Creating the iterators for 2D vector
	int row;
	int col;

	//Connecting establishing every node's vector of adjacent nodes
	for (row = 0; row != 6; ++row)
	{
		for (col = 0; col != 5; ++col)
		{
			//For left adjNode
			if (col - 1 >= 0)
				adjNode->push_back(board[row][col - 1]);
			//For up adjNode
			if (row - 1 >= 0)
				adjNode->push_back(board[row-1][col]);
			//For right adjNode
			if (col + 1 < 4)
				adjNode->push_back(board[row][col + 1]);
			//For down adjNode
			if (row + 1 < 5)
				adjNode->push_back(board[row + 1][col]);
		}
	}
	return *adjNode;
}
//Count the amount of points
int VGMap::countPoints()
{
	//Attributes
	int totalPoints = 0;
	int addedPoints = 0;
	bool flipped = false, filled = true;

	//Count points for each row (HORIZONTALLY)
	for (int row = 0; row < 6; ++row)
	{
		totalPoints += addedPoints;
		for (int col = 0; col < 5; ++col)
		{
			//Check if every node of the same row has a building
			if ((*board)[row][col].getBuilding() != NULL)
			{
				if ((*(*board)[row][col].getBuilding()).isFlipped() == true)
				{
					flipped = true;
				}
			}
			else
			{
				filled = false;
				break;
			}
		}
		//Adding only if the rows are filled + counting doubles if flipped
		if (filled)
		{
			if (!flipped) totalPoints += 2 * 6-row;
			else totalPoints += 6-row;
		}
	}
	//Count points for each row (Vertically)
	for (int col = 0; col < 5; ++col)
	{
		for (int row = 0; row < 6; ++row)
		{
			//Check if every node of the same row has a building
			if ((*board)[row][col].getBuilding() != NULL)
			{
				if ((*(*board)[row][col].getBuilding()).isFlipped() == true)
				{ 
					flipped = true;
				}
			}
			else
			{
				filled = false;
				break;
			}
		}
		//Adding only if the rows are filled + counting doubles if flipped
		if (filled)
		{
			if (flipped) totalPoints += 2 * (3 + abs(3 - col));
			else totalPoints += 3 + abs(3 - col);
		}
	}
	return totalPoints;
}
//Check if it's the first building of the inputed resource
bool VGMap:: checkFirst(int resource)
{
	//Creating the iterators for 2D vector
	int row;
	int col;
	for ( row =0; row < 6; row ++) {
		for (col = 0; col < 5; col++) {
			if ((*(*board)[row][col].getBuilding()).getLabel() == resource) {
				return false;
			}
		}
		
	}
	return true;
};

bool VGMap::canBuild(Building building, int row, int col) {
	bool canBuildNum = true;
	bool canBuildAdj = true;

	//find out how to look for the number...
	VGMap::Node node = (*board)[row][col];
	if (node.getBuilding() != nullptr) {
		return false;
	}
	else {
		if ((building.getNumber()) != 6 - row) {
			return false;
		}
		else {
			if (checkFirst((building.getLabel()))) {
				return true;
			}
			else {
				for (int i = 0; i < (node.getAdjNode()).size(); i++) {
					if (building.getLabel() == node.getAdjNode()[i].getBuilding()->getLabel())
						return true;
				}
			}
	
		}
	}
	return false;
}

void VGMap::build(Building building, int row, int col) {
	if (canBuild(building, row, col)) {
		(*board)[row][col].setBuilding(building);
	}
}


