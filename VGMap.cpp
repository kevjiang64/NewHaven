#include "VGMap.h"
#include "Resources.h"
#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

//VGMap Constructor (Made for testing)
VGMap::VGMap(int row, int col, string name)
{
	//Create 2D vector of 30 Nodes
	//(0,0) is at the top left
	board = new vector<vector<Node>>;
	if(row == 6 && col == 5 && ( (name.compare("Milford")) == 0 || (name.compare("Stratford")) == 0 || (name.compare("Guilford")) == 0 || (name.compare("Fairfield")) == 0) )
	{
		nameOfBoard = &name;
		cout << "The inputed values for the rows and columns will create a 6x5 VGMap\n";
		for (int i = 0; i < row; i++) 
		{
			cout << "Pushing Back Row " << i <<"\n";
			vector<Node> column(col);
			(*board).push_back(column);
		}
		cout << "\n";
		//Put adj nodes for every node
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				cout << "("<<i<<","<<j<<") Filled\n";
				Node node = (*board)[i][j];
				vector<Node> vect = node.fillAdjNodes(*board, i, j);
				node.setAdjNode(vect);
			}
		}
		points = new int();
		*points = 0;
	}
	else
	{
		if (row != 6)
			cout << "The inputed value for the row is not valid" << "\n";
		if (col != 5)
			cout << "The inputed value for the column is not valid" << "\n";
		if((name.compare("Milford")) != 0 || (name.compare("Stratford")) != 0 || (name.compare("Guilford")) != 0 || (name.compare("Fairfield")) != 0)
			cout << "The inputed value for the board is not valid" << "\n";
		exit(0);
	}
};
//VgMap Default Constructor 
VGMap::VGMap()
{
	//Assign a random name to each board
	string boardName[4] = { "Milford","Fairfield","Stratford","Guilford" };
	nameOfBoard = &boardName[rand() % 4];
	board = new vector<vector<Node>>;

	//Create 2D vector of 30 Nodes
	//(0,0) is at the top left	
	for (int i = 0; i < 6; i++)
	{
		cout << "Pushing Back Row " << i << "\n";
		vector<Node> column(5);
		(*board).push_back(column);
	}
	//Put adj nodes for every node
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << "(" << i << "," << j << ") Filled\n";
			Node node = (*board)[i][j];
			vector<Node> vect = node.fillAdjNodes(*board, i, j);
			node.setAdjNode(vect);
		}
	}
	points = new int();
	*points = 0;
};

VGMap::Node::Node() {
	building = new Building();
	building->setLabel(-1);
	building->setNumber(-1);
	adjNode = new vector<Node>;
}
//Fill the board
//Clockwise => 0 : left , 1 : up, 2 : right, 3 : down
vector<VGMap::Node> VGMap::Node::fillAdjNodes(vector <vector<VGMap::Node>> board, int row, int col) {

	cout << "row: " << row << " col: " << col << "\n";
	//For left adjNode
	if (col - 1 >= 0)
	{
		cout << "Linking to Left Node:("<< row <<","<< col-1 << ")\n";
		adjNode->push_back(board[row][col - 1]);
	} 
	//For up adjNode
	if (row - 1 >= 0)
	{
		cout << "Linking to Up Node:(" << row-1 << "," << col << ")\n";
		adjNode->push_back(board[row - 1][col]);
	}
	//For right adjNode
	if (col + 1 <= 4)
	{
		cout << "Linking to Right Node:(" << row << "," << col+1 << ")\n";
		adjNode->push_back(board[row][col + 1]);
	}
	//For down adjNode
	if (row + 1 <= 5)
	{
		cout << "Linking to Down Node:(" << row+1 << "," << col << ")\n";
		adjNode->push_back(board[row + 1][col]);
	}
	cout << "Finish connecting the adjacents nodes for (" <<row<<","<<col<<")\n\n";
	return *adjNode;
}
//Count the amount of points
int VGMap::countPoints()
{
	//Attributes
	//cout << "" << endl;
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
			if ((*board)[row][col].getBuilding()->getLabel() != -1 )
			{
					
				filled = true;
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
			
			if (!flipped) totalPoints += 2 * (6-row);
			else totalPoints += 6-row;
			
		}
	}
	//Count points for each row (Vertically)
	for (int col = 0; col < 5; ++col)
	{
		for (int row = 0; row < 6; ++row)
		{
			
			//Check if every node of the same row has a building
			if ((*board)[row][col].getBuilding()->getLabel() != -1)
			{
				filled = true;
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
			if (!flipped) totalPoints += 2 * (3 + abs(3 - (col+1)));
			else totalPoints += 3 + abs(3 - (col+1));
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

bool VGMap::canBuild(Building* building, int row, int col) {
	
	bool canBuildNum = true;
	bool canBuildAdj = true;

	VGMap::Node node = (*board)[row][col];
	
	if (node.getBuilding() == nullptr) {
		return false;
	}
	else {
		if ((building->getNumber()) != 6 - row) {
			return false;
		}
		else {
			if (checkFirst((building->getLabel()))) {
				return true;
			}
			else {
				for (int i = 0; i < (node.getAdjNode()).size(); i++) {
					if (building->getLabel() == node.getAdjNode()[i].getBuilding()->getLabel())
						return true;
				}
			}
	
		}
	}
	return false;
}

void VGMap::build(Building* building, int row, int col) {
	//if (canBuild(building, row, col)) {
		(*board)[row][col].setBuilding(*building);
	//}
}

void VGMap::displayVGmap() {
	for (int row = 0; row < 6; row++)
	{
		cout << 6-row << " ";
		for (int col = 0; col < 5; col++)
		{
			//If the position possess a building
			if ((*board)[row][col].getBuilding() != NULL)
			{
				string flipped, resources;
				int label = (*(*board)[row][col].getBuilding()).getLabel();
				//Attributing a resource based on the label (0: meadow, 1: quarry, 2: forest, 3: wheatfield)
				switch (label)
				{
				case 0: resources = "M";
					break;
				case 1: resources = "Q";
					break;
				case 2: resources = "F";
					break;
				case 3: resources = "W";
					break;
				}
				//Value of the building
				int number = (*(*board)[row][col].getBuilding()).getNumber();

				//Giving flipped string F or NF
				if ((*(*board)[row][col].getBuilding()).isFlipped())
				{
					flipped = "f";
				}
				else
				{
					flipped = " ";
				}
				if (number == -1) {
					cout << "|   ";
				}
				else {
					//Printing each building
					cout << "|" << number << resources << flipped;
				}
				
			}
			else
			{
				//Printing empty building
				cout << "|   ";
			}
		}
		//Going to next row
		cout << "|\n";
	}
	cout << "  ";
	for (int i = 1; i < 6; i++) {
		cout << "  " << i << " ";
	}
	cout << "" << endl;
}

//Display the VGMap 
void VGMap::display() {
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			//If the position possess a building
			if ((*board)[row][col].getBuilding() != NULL)
			{
				string flipped, resources;
				int label = (*(*board)[row][col].getBuilding()).getLabel();
				//Attributing a resource based on the label (0: meadow, 1: quarry, 2: forest, 3: wheatfield)
				switch (label)
				{
				case 0: resources = "M";
					break;
				case 1: resources = "Q";
					break;
				case 2: resources = "F";
					break;
				case 3: resources = "W";
					break;
				}
				//Value of the building
				int number = (*(*board)[row][col].getBuilding()).getNumber();
				//Giving flipped string F or NF
				if ((*(*board)[row][col].getBuilding()).isFlipped())
				{
					flipped = "F";
				}
				else
				{
					flipped = "NF";
				}
				//Printing each building
				cout << "|" << number << resources << flipped << "|";
			}
			else
			{
				//Printing empty building
				cout << "|   |";
			}
		}
		//Going to next row
		cout << "\n";
	}
}

int VGMap::numberOfEmptySpaces() {
	int countEmptySpaces = 0;
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			int number = (*(*board)[row][col].getBuilding()).getNumber();
			if (number == -1) {
				countEmptySpaces++;
			}
		}
	}
}

