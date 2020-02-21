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
	Resources amountOfResources;
public:
	class Resources
	{
	private:
		int* stone;
		int* sheep;
		int* weat;
		int* wood;

	public:
		//Constructors
		Resources(int stone, int sheep, int weat,int wood);
		Resources(int& stone, int& sheep, int& weat, int& wood);
		//Getters
		inline int getStone() { return *stone };
		inline int getSheep() { return *sheep };
		inline int getWeat() { return *weat };
		inline int getWood() { return *wood };
		//Setter
		inline void setStone(int stone) { this.stone = stone; };
		inline int setSheep(int sheep) { this.*sheep = sheep };
		inline int setWeat(int weat) { this.*weat = weat; };
		inline int setWood(int wood) { this.*wood = wood; };
	}
	//Constructors
	Player(Resources amount, VGMap playerMap, vector <Tile> resourceVect, vector <Building> buildingVect);
	Player(Resources& amount, VGMap& playerMap, vector <Tile*>* resourceVect, vector <Building*>* buildingVect );
	//Getters
	inline VGMap getPlayerMap() { return *playerMap };
	inline vector <Tile> getResourceVect() { return *resourceVect };
	inline vector <Building> getBuildingVect() { return *buildingVect };
	//Methods to be used by the player
	Tile randomTile();
	Building randomBuilding();
	void PlaceHarvestTile(, int row, int column); //Game Board as first argument
	Building DrawBuilding();
	Tile DrawHarvestTile();
	void ResourceTracker(Resources playerResources);
	void BuildVillage(VGMap playerMap, Building placed, int row, int column);
	Resources CalculateResources(Building placed); //Game Board as first argument
};