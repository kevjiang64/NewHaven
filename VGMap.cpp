#include "VGMap.h"
#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

//Building Constructor (pass by value)
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
};
//VGMap Constructor (pass by value)
VGMap::VGMap(vector<Building> board, int points, vector<Building> adjBuilding)
{
	this.board(board.begin(), board.end());
	*points = points;
	this.adjBuild(adjBuild.begin().adjBuild.end());
};
//VGMap Constructor (pass by reference)
VGMap::VGMap(vector<Building>* board, int* points, vector<Building>* adjBuilding)
{
	this.board(board.begin(), board.end());
	*points = points;
	this.adjBuild(adjBuild.begin().adjBuild.end());
};
//Add Building to VGMap
VGMap :: void addBuilding(Building building)
{
	board.push_back(building);
};
//Add Edge from a building to another
VGMap :: void addEdge(int from, int to)
{
	(*board)[from - 1]->getAdjBuilding()->push_back((*board)[to - 1]);
	(*board)[to - 1]->getAdjBuilding()->push_back((*board)[from - 1]);
};
//Check if the board is connected ??????
VGMap :: bool checkConnected()
{

}
//Count the amount of points
VGMap :: int countPoints(vector<Building> vect)
{
	int totalPoints = 0;
	for (std::vector<int>::iterator it = vect.begin(); it != vect.end(); ++it)
	{
		Building test = *it;
		if (*(test.getFlipped()) == true);
	}
}
//Check if it's the first building of the inputed resource
VGMap :: bool checkFirst(Building newBuilding, vector<Building> vect)
{
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
