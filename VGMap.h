#include <string>
#include <vector>
#include <set>
#include <iostream>
#include "Resources.h"
using namespace std;

#ifndef VGMap_h
#define VGMap_h

//modified the order of the public and private variables/functions
class VGMap
{
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
        inline void setAdjNode(vector<Node> vect) { *adjNode = vect; };
        //Methods
        vector<VGMap::Node> fillAdjNodes(vector <vector<VGMap::Node>> board, int row, int col);
        //For Testing
        inline int getSize() { return adjNode->size();};
    };
    //Constructors
    VGMap(int row, int col, string nameOfBoard);
    VGMap();
    //Getters
    inline vector<vector<Node>> getBoard(){ return *board; };
    inline int getPoints(){ return *points; };
    //Methods
    int countPoints();
    bool checkFirst(int resource);
    bool canBuild(Building* building, int row, int col);
    void build(Building* building, int row, int col);
    void displayVGmap();
    void display();
    int numberOfEmptySpaces();
//Attributes
private:
	vector<vector<Node>>* board;
	int* points;
	string* nameOfBoard;
};

#endif 
