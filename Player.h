#include <VGMap.h>
#include <vector>
#include <VGMap.cpp>
#include <string>
#include <set>
#include <iostream>
using namespace std;

class Player
{
private:
	//Attributes
	VGMap* playerMap;
	vector <Tile>* resourceVect;
	vector <Building>* buildingVect;
public:
	//Constructors
	Player(VGMap playerMap, vector <Tile> resourceVect, vector <Building> buildingVect);
	Player(VGMap& playerMap, vector <Tile*>* resourceVect, vector <Building*>* buildingVect );
	void PlaceHarvestTile(, int row, int column); //Game Board as first argument
	Building DrawBuilding();
	Tile DrawHarvestTile();
	void ResourceTracker(vector <Tile>* resourceVect);
	void BuildVillage(VGMap playerMap, int row, int column);
	int CalculateResources(); //Game Board as first argument
};