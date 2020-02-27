#include <string>
#include <vector>
#include <set>
#include <iostream>
#include "Resources.h"
using namespace std;

#ifndef VGMap_h
#define VGMap_h

class VGMap
{
	class Node;
//Attributes
private:
	vector<vector<Node>>* board;
	int* points;
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
		vector<VGMap::Node> fillAdjNodes(vector <vector<VGMap::Node>> board);
	};
	//Constructors
	VGMap ();
	//Getters
	inline vector<vector<Node>> getBoard(){ return *board; };
	inline int getPoints(){ return *points; };
	//Methods
	int countPoints();
	bool checkFirst(int resource);
	bool canBuild(Building building, int row, int col);
	void build(Building building, int row, int col);
};

#endif 