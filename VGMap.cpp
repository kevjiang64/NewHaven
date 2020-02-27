#include "VGMap.h"
#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

//VGMap Constructor (pass by value)
VGMap::VGMap()
{
	//Create 2D vector of 30 Nodes
	//(0,0) is at the top left	
	*board = board{ 6, vector<Node> {5} };
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
				(*adjNode)[0] = board[row][col - 1];
			else {
				VGMap::Node* ptrNode;
				*ptrNode = (*adjNode).at(0);

				ptrNode = nullptr;
			}
				
			//For up adjNode
			if (row - 1 >= 0)
				(*adjNode)[1] = board[row-1][col];
			else {
				VGMap::Node* ptrNode;
				*ptrNode = (*adjNode).at(1);

				ptrNode = nullptr;
			}
			//For right adjNode
			if (col + 1 < 4)
				(*adjNode)[2] = board[row][col + 1];
			else {
				VGMap::Node* ptrNode;
				*ptrNode = (*adjNode).at(2);

				ptrNode = nullptr;
			}
			//For down adjNode
			if (row + 1 < 5)
				(*adjNode)[3] = board[row + 1][col];
			else {
				VGMap::Node* ptrNode;
				*ptrNode = (*adjNode).at(3);

				ptrNode = nullptr;
			}
		}
	}
	return *adjNode;
}
//Count the amount of points
int VGMap::countPoints(vector<Node> vect)
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
			if (board[row][col].getBuilding != NULL)
			{
				if (board[row][col].getBuilding.getFlipped() == true)
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
			if (row == 0 || flipped = false)
				totalPoints += 6 * 2;
			else {
				totalPoints += 6;
			}
			if (row == 1 || flipped = false)
				totalPoints += 5 * 2;
			else {
				totalPoints += 5;
			}
			if (row == 0 || flipped = false)
				totalPoints += 4 * 2;
			else {
				totalPoints += 4;
			}
			if (row == 0 || flipped = false)
				totalPoints += 3 * 2;
			else {
				totalPoints += 3;
			}
			if (row == 0 || flipped = false)
			{
				totalPoints += 2 * 2;
			}
			else {
				totalPoints += 2;
			}
			if (row == 0 || flipped = false) {
				totalPoints += 1 * 2;
			}
			else {
				totalPoints += 1;
			}
		}
	}
	//Count points for each row (Vertically)
	for (col = 0; col < 5; ++col)
	{
		for (row = 0; row < 6; ++row)
		{
			//Check if every node of the same row has a building
			if (board[row][col].getBuilding != NULL)
			{
				if (board[row][col].getBuilding.getFlipped() == true)
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
			if (col == 0 || flipped = false) {
				totalPoints += 5 * 2;
			}
			else {
				totalPoints += 5;
			}
			if (col == 1 || flipped = false) {
			totalPoints += 4 * 2;
			}
			else {
				totalPoints += 4;
			}
			if (col == 2 || flipped = false){
				totalPoints += 3 * 2;
			}
			else {
				totalPoints += 3;
			}
			if (col == 3 || flipped = false) {
				totalPoints += 4 * 2;
			}
			else {
				totalPoints += 4;
			}
			if (col == 4 || flipped = false) {
				totalPoints += 5 * 2;
			}
			else {
				totalPoints += 5;
			}
		}
	}
	return totalPoints;
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
