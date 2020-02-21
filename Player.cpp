#include <VGMap.h>
#include <vector>
#include <VGMap.cpp>
#include <Player.h>
#include <string>
#include <set>
#include <iostream>
using namespace std;

class Player
{
	//Constructor passed by value
public:
	Player(Resources amount,VGMap playerMap, vector <Tile> harvestVect, vector <Building> buildingVect)
	{
		this.*amountOfResource = amount;
		this.*playerMap = playerMap;
		this.*resourceVect = harvestVect;
		this.*buildingVect = buildingVect;
	}
	//Constructor passed by reference
	Player(Resources& amount, VGMap& playerMap, vector <Tile*>* harvestVect, vector <Building*>* buildingVect)
	{
		this.*amountOfResources = amount;
		this.*playerMap = playerMap;
		this.*harvestVect = harvestVect;
		this.*buildingVect = buildingVect;
	}
	//Method to calculate the amount of resources???
	Resources CalculateResources(Building placed)
	{

	};
	//Method to place tiles in game board 
	void PlaceHarvestTile(int row, int column, ) //Board parameter
	{

	};
	//Method to place building in player board
	bool BuildVillage(VGMap playerMap, int row, int column, Building playerBuilding)
	{
		//Build Village only if the space is available
		if(*(playerMap.getBoard())[row][column] == NULL)
		{ 
			*(playerMap.getBoard())[row][column]->push_back(playerBuilding);
			return 0;
		}
		//Otherwise...
		cout << "The place is currently occupied by a building. Please Pick again";
		return 1;
	}
	//Generating a random village/building???
	Building randomBuilding()
	{
		//Random number range for resources and ID
		int numResources = rand() % (7 - 1) + 1;
		int numID = rand() % (121 - 1) + 1;
		//Random string generator for type of resource
		string resourcesTypes[] = "wood" "weat" "sheep" "stone";
		string randType = resourcesTypes[rand() % sizeof(resourcesTypes) - 1];
		Building random = Building(numberResources, true, numID, randType);
		return random;
	}
	//Adding a random Building to the vector
	Building DrawBuilding()
	{
		buildingVect->push_back(randomBuilding());
	};
	//Generating a random village/building???
	Building randomTile()
	{

	};
	//Adding a random Harvest Tile to the vector
	Tile DrawHarvestTile()
	{
		harvestVect->push_back(randomTile());
	};
	//Tracker for the amount of resources in one turn
	void ResourceTracker(Resources playerResources)
	{
		cout << "The amount of stones left is " playerResources.getStone();
		cout << "The amount of weats left is " playerResources.getWeat();
		cout << "The amount of sheeps left is " playerResources.getSheep();
		cout << "The amount of wood left is " playerResources.getWood();
	};

};