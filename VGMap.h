#include <string>
#include <vector>
#include <set>
#include <iostream>
#include "GBMaps.h"
using namespace std;

class VGMap
{
//Attributes
public:
	//Inner class
	class Node
	{
	private:
		Building* resource;
		vector<Node>* adjNode;
	public:
		//Constructors
		Node();
		//Getters
		inline Building getResource{ return *resource; };
		inline vector<Node> getAdjNode{ return *adjNode; };
		//Methods
		vector<Node> fillAdjNodes(vector <vector<Node>> board);
	};
	//Constructors
	VGMap (int points);
	//Getters
	inline vector<Node> getBoard{ return *board; };
	inline int getPoints{ return *points; };
	//Setters
	inline void setBoard(vector <Node> board)
	{
		this.board(board.begin(), board.end());
	}
	inline void setPoints(int points)
	{
		this.points = points;
	}
	//Methods
	int countPoints(vector<> vect);
	bool checkFirst(Building newBuilding, vector<Building> vect);
private:
	vector <vector<VGMap::Node*>> board = (5, vector<Node*>(6));
	int* points;
};

#endif 