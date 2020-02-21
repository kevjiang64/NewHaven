#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

class VGMap
{
//Attributes
private:
	vector<Building>* board;
	int* points;
	vector<Building>* adjBuilding;
public:
	class Building
	{
	private:
		int* buildingID;
		int* numOfResources;
		bool* flipped;
		string* resourceType;
	public:
		//Constructors
		Building(int numOfResources, bool flipped, int buildingID, string resourceType);
		Building(int& numOfResources, bool& flipped, int& buildingID, string& resourceType);
		//Getters
		inline int getNumberOfResources{ return *numOfResources; }
		inline bool getFlipped{ return *flipped; }
		inline string getResourceType{ return *resourceType; }
		inline int getBuildingID{ return *buildingID };
		//Setters
		inline void setNumberOfResources(int number) 
		{
			*numOfResources = number;
		}
		inline void setFlipped(bool flip)
		{
			*flipped = flip;
		}
		inline void setResourceType(string type)
		{
			*resourceType = type;
		}
		//Methods
		void flipping();
	};
	//Constructors
	VGMap(vector<Building> board, int points, vector<Building> adjBuilding);
	VGMap(vector<Building*>* board, int& points, vector<Building*>* adjBuilding);
	//Getters
	inline vector<Building*>* getAdjBuilding{ return *adjBuilding; }
	inline vector<Building> board{ return *adjBuilding; }
	inline int getPoints{ return *points; }
	//Setters
	inline void setBoard(vector <Building> board)
	{
		this.board(board.begin(), board.end());
	}
	inline void setPoints(int points)
	{
		this.points = points;
	}
	inline void setAdjBuilding(vector <Building> adjBuilding)
	{
		this.adjBuilding(adjBuilding.begin(),)
	}
	//Methods
	void addBuilding(Building newBuilding);
	void addEdge(int from, int to); //?
	int countPoints(vector<Building> vect);
	bool checkConnected(); //?
	bool checkFirst(Building newBuilding, vector<Building> vect);
};

#endif 