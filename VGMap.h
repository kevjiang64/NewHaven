#include <string>
#include <vector>
#include <set>
#include <iostream>
<<<<<<< HEAD
#include "GBMaps.h"
=======
#include "Resources.h"
>>>>>>> 97f213f11be08ca159a6c69ba8f367c2ebfa0f5b
using namespace std;

#ifndef VGMap_h
#define VGMap_h

class VGMap
{
	class Node;
//Attributes
<<<<<<< HEAD
=======
private:
	vector<vector<Node>>* board;
	int* points;
>>>>>>> 97f213f11be08ca159a6c69ba8f367c2ebfa0f5b
public:
	//Inner class
	class Node
	{
	private:
		Building* building;
		vector<Node>* adjNode;
	public:
		//Constructors
		Node();
		//Getters
		inline Building* getBuilding(){ return building; };
		inline vector<Node> getAdjNode(){ return *adjNode; };
		//Setters
		inline void setBuilding(Building building2) { *building = building2; };
		//Methods
		vector<Node> fillAdjNodes(vector <vector<Node>> board);
	};
	//Constructors
	VGMap ();
	//Getters
	inline vector<vector<Node>> getBoard(){ return *board; };
	inline int getPoints(){ return *points; };
	//Methods
<<<<<<< HEAD
	int countPoints(vector<> vect);
	bool checkFirst(Building newBuilding, vector<Building> vect);
private:
	vector <vector<VGMap::Node*>> board = (5, vector<Node*>(6));
	int* points;
=======
	int countPoints();
	bool checkFirst(int resource);
	bool canBuild(Building building, int row, int col);
	void build(Building building, int row, int col);
>>>>>>> 97f213f11be08ca159a6c69ba8f367c2ebfa0f5b
};

#endif 