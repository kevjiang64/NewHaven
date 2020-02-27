#include "VGMap.h"
#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

/*//Building Constructor (pass by value)
Building::Building(int numOfResources, bool flipped, int buildingID, string resourceType)
{
	*numOfResources = numOfResources;
	*flipped = flipped;
	*buildingID = building;
	*resourceType = resourceType;
};
//Building Constructor (pass by reference)
Building::Building(int& numOfResources, bool& flipped, int& buildingID, string& resourceType)
{
	*numOfResources = numOfResources;
	*flipped = flipped;
	*buildingID = building;
	*resourceType = resourceType;
};
//Flipping method
Building :: void flipping()
{
	if (*flipped == true)
	{
		*flipped = false;
	}
	else
	{
		*filled = true;
	}
};*/
//VGMap Constructor (pass by value)
VGMap::VGMap()
{
	//Create 2D vector of 30 Nodes
	//(0,0) is at the top left	
	*board = board{ 6, vector<Node> {5} };
	
	//Fill the board up.
	//Clockwise => 0 : left , 1 : up, 2 : right, 3 : down
	fillAdjNodes(*board);
};
//Fill the board
VGMap::vector<Node> fillAdjNodes(vector < vector <Node> > board) {

	//Creating the iterators for 2D vector
	std::vector< std::vector<int> >::const_iterator row;
	std::vector<int>::const_iterator col;

	//Connecting establishing every node's vector of adjacent nodes
	for (row = board.begin(); row != board.end(); ++row)
	{
		for (col = row->begin(); col != row->end(); ++col)
		{
			//For left adjNode
			if (col - 1 >= 0)
				adjBuilding[0]->board[row][col - 1];
			else
				adjBuidling[0]->NULL;
			//For up adjNode
			if (row - 1 >= 0)
				adjBuilding[1]->board[row - 1][col];
			else
				adjBuilding[1]->NULL;
			//For right adjNode
			if (col + 1 < 4)
				adjBuilding[1]->board[row][col + 1];
			else
				adjBuilding[1]->NULL;
			//For down adjNode
			if (row + 1 < 5)
				adjBuilding[2]->board[row - 1][col];
			else
				adjBuilding[2]->NULL;
		}
	}
};
//Count the amount of points
VGMap :: int countPoints(vector<Building> vect)
{
	int totalPoints = 0;
	for (std::vector<int>::iterator it = vect.begin(); it != vect.end(); ++it)
	{
		Building test = *it;
		
	}
}
//Check if it's the first building of the inputed resource
VGMap :: bool checkFirst()
{
	//Creating the iterators for 2D vector
	std::vector< std::vector<int> >::const_iterator row;
	std::vector<int>::const_iterator col;
	for (std::vector<int>::iterator it = vect.begin(); it != vect.end(); ++it)
	{

		Building test = *it;
		if (*(test.getResourceType()).compare(*(newBuilding.getResourceType())) == 0) 
		{
			return false;
		}
	}
	return true;
};
