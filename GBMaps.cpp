//
//  GBMaps.cpp
//  COMP345_A1
//
//  Created by Justin Teixeira on 2020-02-10.
//  Copyright © 2020 Justin Teixeira. All rights reserved.
//

#include "Resources.h"

#include <stdio.h>
#include "GBMaps.h"
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

/**
 Map default constructor
*/
Map::Map() {

}


/**
 * Map constructor
 *
 * @param playerNumber number of players for the map
 * @param nodes  the node vector
 */


Map::Map(int playerNumber, std::vector<Node> nodes) {
    playerNum = new int(playerNumber);
    mapNodes = new std::vector<Node*>;
}

/**
 * Map copy constructor
 * @param toCopy copy constructor
 */
Map::Map(const Map& toCopy) {
    playerNum = new int();
    mapNodes = new vector<Node*>;
    *playerNum = *toCopy.playerNum;
    *mapNodes = *toCopy.mapNodes;
}

/**
 * Map destructor
 */
Map::~Map() {
    delete playerNum;
    delete mapNodes;
}

/**
 * assignment operator
 * @param rhs right hand side operator
 */
void::Map::operator=(Map& rhs) {
    this->playerNum = rhs.playerNum;
    this->mapNodes = rhs.mapNodes;
}

/**
* Tile default constructor
*/

Map::Tile::Tile() {

}

/**
* Tile constructor
*/
/*Map::Tile::Tile(Node topLeft, Node topRight, Node bottomRight, Node bottomLeft) {
    Node topLeft = Node();
    Node topRight = Node();
    Node bottomRight = Node();
    Node bottomLeft = Node();
}*/

/**
* Tile destructor
*/
Map::Tile::~Tile() {
    delete topLeft;
    delete topRight;
    delete bottomRight;
    delete bottomLeft;
}


void Map::Tile::operator=(Map::Tile& rhs) {
    this->topLeft = rhs.topLeft;
    this->topRight = rhs.topRight;
    this->bottomRight = rhs.bottomRight;
    this->bottomLeft = rhs.bottomLeft;
}

Map::Tile::Tile(const Tile& toCopy) {
    topLeft = new Node();
    *topLeft = *toCopy.topLeft;
    topRight = new Node();
    *topRight = *toCopy.topRight;
    bottomRight = new Node();
    *bottomRight = *toCopy.bottomRight;
    bottomLeft = new Node();
    *bottomLeft = *toCopy.bottomLeft;
}



/**
 * Node default constructor
 */

Map::Node::Node() {

}


/**
 * Node constructor, subclass of Map
 *
 */
Map::Node::Node(int resource, std::vector<Node> pAdjNode, bool counted) {
    resourceType = new int();
    pAdjNodes = new std::vector<Node*>;
    isCounted = new bool(false);
}

/**
 * Node destructor
 */
Map::Node::~Node() {
    //delete& resourceType;
    //delete& pAdjNodes;
    //delete& isCounted;
}

/**
* Node operator
*/
void Map::Node::operator=(Map::Node& rhs) {
    this->resourceType = rhs.resourceType;
    this->pAdjNodes = rhs.pAdjNodes;
    this->isCounted = rhs.isCounted;
}

/**
* Node copy constructor
*/
Map::Node::Node(const Node& toCopy) {
    resourceType = new int();
    if (toCopy.resourceType != nullptr) *resourceType = *toCopy.resourceType;
    pAdjNodes = new std::vector<Node*>;
    if (toCopy.pAdjNodes != nullptr) *pAdjNodes = *toCopy.pAdjNodes;
    isCounted = new bool();
    if (toCopy.isCounted != nullptr) *isCounted = *toCopy.isCounted;
}

/**
 * Add connection between two nodes
 *
 */
Map::Node* Map::addNode(int resource, std::vector<Node> pAdjNode, bool counted) {
    //create graph node
    auto* thisNode = new Node(resource, pAdjNode, counted);
    //add node to graph
    mapNodes->push_back(thisNode);
    return thisNode;
}

/**
 * Add edge to neighboot node
 *
 */
void Map::addEdge(int from, int to) {
    //each node maintains a list of pointers to all neighboor nodes
    (*mapNodes)[from - 1]->getAdjNodes()->push_back((*mapNodes)[to - 1]);
}

/**
 * Test if the map is a connected graph.
 *
 * @return true if the map is a connected graph
 */
bool Map::testConnected() {
    //test overall graph
    if (testIndividualGraph(this->mapNodes, false)) {
        //test subgraphs
        for (auto node : *this->mapNodes) {
            if (node->getAdjNodes()->size() == 1) {
                continue;
            }
            else if (!testIndividualGraph(node->getAdjNodes(), true)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Map::testIndividualGraph(std::vector<Node*>* toTest, bool isVisited) {
    auto* visitedNodes = new std::set<int*>;
    //recurse through graph with an arbitrary starting point, if we visit all the nodes in graph then its connected.
    dfs(visitedNodes, toTest[0][0], isVisited);
    bool connected = visitedNodes->size() == toTest->size();
    delete (visitedNodes);
    return connected;
}

/**
 * Test if the map is a connected graph.
 * recurse through all adjacent nodes from starting point and add node number to list. If all the nodes are in the list after the recursion, then map is fully connected
 *
 * @param visitedNodes a list of visited node
 * @param node the node we are analyzing
 */
void Map::dfs(std::set<int*>* visitedNodes, Node* node, bool nodeTest) {
    if (visitedNodes->find(node->getResourceType()) == visitedNodes->end()) {
        visitedNodes->insert(node->getResourceType());
        for (auto& n : *node->getAdjNodes()) {
            if (!nodeTest || n->getResourceType() == node->getResourceType()) {
                dfs(visitedNodes, n, nodeTest);
            }
            else {
                continue;
            }
        }
    }
}

/*void Map::placeHarvestTile(Map::Tile tile) {
    Node topLeft = *tile.getTopLeft();
    Node topRight = *tile.getTopRight();
    Node bottomRight = *tile.getBottomRight();
    Node bottomLeft = *tile.getBottomLeft();
}*/

/**
*  From a Harvest Tile, creates 4 new nodes, sets their adjacency just within the tile (since no position), and places it in the map
*/
void Map::placeHarvestTile(HarvestTile tile) {
    vector<Node> newNodes = *(new vector<Node>);
    for (int i = *(tile.getTopLeft()); i < 4; i++) {
        Node newNode;
        newNode.setResourceType(&(tile.getResources()[i]));
        newNodes.push_back(newNode);
        cout << "PlaceHarvestTile: resource added " << i <<"-->" << tile.getResources()[i] << endl;
    }
    for (int i = 0; i < *(tile.getTopLeft()); i++) {
        Node newNode;
        newNode.setResourceType(&(tile.getResources()[i]));
        newNodes.push_back(newNode);
        cout << "PlaceHarvestTile: resource added " << i << "-->" << tile.getResources()[i] << endl;
    }
    //now we have a vector of 4 nodes in the right order
    
    //set adjacency within the nodes of the tile itself (i.e. suppose we place the tile adjacent to nothing)
    for (int i = 0; i < 4; i++) {
        if (i + 1 < 4) {
            (*(newNodes[i].getAdjNodes())).push_back(&(newNodes[i + 1]));
        }
        if (i + 3 < 4) {
            (*(newNodes[i].getAdjNodes())).push_back(&(newNodes[i + 3]));
        }
        if (i - 1 >= 0) {
            (*(newNodes[i].getAdjNodes())).push_back(&(newNodes[i - 1]));
        }
        if (i - 3 >= 0) {
            (*(newNodes[i].getAdjNodes())).push_back(&(newNodes[i - 3]));
        }
    }

    //place in the map
    for (int i = 0; i < 4; i++) {
        (*mapNodes).push_back(&newNodes[i]);
    }
    
}

