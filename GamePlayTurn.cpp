#include <vector>
#include <iostream>
#include "GBMaps.h"
#include "VGMap.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "Player.h"
#include "Resources.h"
#include "Part6.h"

//Method Signature
void buildPlayerVillage(Player& player);
bool enoughResources(Player& player, int index);
void removeUsedResources(Player& player,int index);

//Place a building in the VGMap board
void buildPlayerVillage(Player& player)
{
	int row, col, index;
	bool result = false;

	//Checking what building and where to put it
	cout << "Which building do you want to place in board? (0-?)" << "\n";
	cin >> index;
	cout << "On which row do you want to place the building? (0-5)" << "\n";
	cin >> row;
	cout << "On which column do you want to place the building? (0-5)" << "\n";
	cin >> col;

	//Showing player's resources
	player.getHand()->printResources;

	//Checking if player has enough resources
	if (enoughResources(player,index))
	{
		//Method return true if the village is successfully put
		result = player.buildVillage(index, row, col);
	}
	else
	{
		cout << "Player can't doesn't have enough resources" << "\n";
	}
	//Reducing the number of resources of player's hand
	if (result)
	{
		removeUsedResources(player, index);
	}
	//Showing player's new resources
	player.getHand()->printResources;

}
//Check if player has enough resources
bool enoughResources(Player& player,int index)
{
	//Type of resources
	int buildingResource = player.getBuildings().at(index).getLabel();
	//Number of resources
	int resourceAmount = player.getBuildings().at(index).getNumber();

	return (player.getHand()->getResourceMarkers()->at(buildingResource) > resourceAmount);
}
//Remove used resources
void removeUsedResources(Player& player, int index)
{
	int buildingResource = player.getBuildings().at(index).getLabel();
	int resourceAmount = player.getBuildings().at(index).getNumber();

	player.getHand()->getResourceMarkers()->at(buildingResource) -= resourceAmount;
}