//
//  GBMaps.cpp
//  COMP345_A1
//
//  Created by Justin Teixeira on 2020-02-10.
//  Copyright © 2020 Justin Teixeira. All rights reserved.
//

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
Map::Map(){
    
}


/**
 * Map constructor
 *
 * @param playerNumber number of players for the map
 * @param nodes  the node vector
 */


Map::Map(int playerNumber, std::vector<std::vector<std::string>> nodes) {
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

Map::Tile::Tile(){
    
}

/**
* Tile constructor
*/
Map::Tile::Tile(Node topLeft, Node topRight, Node bottomRight, Node bottomLeft){
    topLeft = new Node(std::string resource);
    topRight = new Node(std::string resource);
    bottomRight = new Node(std::string resource);
    bottomLeft = new Node(std::string resource);
}

/**
* Tile destructor
*/
Map::Tile::~Tile(){
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
    topLeft = new Node(std::string resource);
    *topLeft = *toCopy.topLeft;
    topRight = new Node(std::string resource);
    *topRight = *toCopy.topRight;
    bottomRight = new Node(std::string resource);
    *bottomRight = *toCopy.bottomRight;
    bottomLeft = new Node(std::string resource);
    *bottomLeft = *toCopy.bottomLeft;
}



/**
 * Node default constructor
 */

Map::Node::Node(){
    
}


/**
 * Node constructor, subclass of Map
 *
 */
Map::Node::Node(std::string resource) {
    resourceType = new std::string(std::move(resource));
}

/**
 * Node destructor
 */
Map::Node::~Node() {
    delete resourceType;
}

/**
* Node operator
*/
void Map::Node::operator=(Map::Node& rhs) {
    this->resourceType = rhs.resourceType;
}

/**
* Node copy constructor
*/
Map::Node::Node(const Node& toCopy) {
    resourceType = new string();
    *resourceType = *toCopy.resourceType;
}

/**
 * Add connection between two nodes
 *
 */
Map::Node* Map::addNode(std::string resource) {
    //create graph node
    auto* thisNode = new Node(std::move(resource));
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
    if(testIndividualGraph(this->mapNodes,false)){
        //test subgraphs
        for(auto node : *this->mapNodes){
            if(node->getResourceType()->size() == 1){
                continue;
            }else if(!testIndividualGraph(node->getResourceType(),true)){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Map::testIndividualGraph(std::vector<Node*>* toTest, bool isVisited) {
    auto* visitedNodes = new std::set<std::string>;
    //recurse through graph with an arbitrary starting point, if we visit all the nodes in graph then its connected.
    dfs(visitedNodes, toTest[0][0], isVisited);
    bool connected = visitedNodes->size() == toTest->size();
    delete (visitedNodes);
    return connected;
}

/**
 * Test if the map is a connected graph.
 * recurse through all adjacent nodes from starting point and add node number to list. If all the tiles are in the list after the recursion, then map is fully connected
 *
 * @param visitedNodes a list of visited node
 * @param node the node we are analyzing
 */
void Map::dfs(std::set<std::string>* visitedNodes, Node* node, bool nodeTest) {
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

