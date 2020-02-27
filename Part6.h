#pragma once

#include <vector>
#include "VGMap.h"
#include "GBMaps.h"

using namespace std;

class Score {
private:
	VGMap::Node getNextNodeInRow(VGMap::Node currentNode);
	VGMap::Node getPrevNodeInRow(VGMap::Node currentNode);
	VGMap::Node getNextNodeInColumn(VGMap::Node currentNode);
	VGMap::Node getPrevNodeInColumn(VGMap::Node currentNode);
public :
	int countFinalPoints(VGMap villageBoard);
};

class CountResources {
private :
	int recursiveCountResourceFromSquare(int res, Map::Node node);
public: 
	vector<int> calculResourceMarkers(Map board, vector<Map::Node> nodesJustPlaced);
};