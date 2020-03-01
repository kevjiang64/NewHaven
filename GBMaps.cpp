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
#include "Resources.h"
#include "Player.h"
#include "Part6.h"
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
Map::Tile::Tile(Node* topLeft, Node* topRight, Node* bottomRight, Node* bottomLeft) {
    this->topLeft = topLeft;
    this->topRight = topRight;
    this->bottomRight = bottomRight;
    this->bottomLeft = bottomLeft;
}

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
Map::Node::Node(int resource, std::vector<Node*> pAdjNode, bool counted) {
    resourceType = new int(resource);
    pAdjNodes = new std::vector<Node*>(pAdjNode);
    isCounted = new bool(counted);
}

/**
 * Node destructor
 */
Map::Node::~Node() {
    delete& resourceType;
    delete& pAdjNodes;
    delete& isCounted;
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
    *resourceType = *toCopy.resourceType;
    pAdjNodes = new std::vector<Node*>;
    *pAdjNodes = *toCopy.pAdjNodes;
    isCounted = new bool();
    *isCounted = *toCopy.isCounted;
}

/**
 * Add connection between two nodes
 *
 */
Map::Node* Map::addNode(int resource, std::vector<Node*> pAdjNode, bool counted) {
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

vector<Map::Node> Map::placeHarvestTile(HarvestTile tile, int row, int col) {
    //create nodes from the tile
    vector<Node> newNodes = *(new vector<Node>);
    for (int i = *(tile.getTopLeft()); i < 4; i++) {
        Node newNode;
        newNode.setResourceType(&(tile.getResources()[i]));
        newNodes.push_back(newNode);
        cout << "PlaceHarvestTile: resource added " << i << "-->" << tile.getResources()[i] << endl;
    }
    for (int i = 0; i < *(tile.getTopLeft()); i++) {
        Node newNode;
        newNode.setResourceType(&(tile.getResources()[i]));
        newNodes.push_back(newNode);
        cout << "PlaceHarvestTile: resource added " << i << "-->" << tile.getResources()[i] << endl;
    }
    //now we have a vector of 4 nodes in the right order

    //set row col properties
    newNodes[0].setRow(row);
    newNodes[0].setCol(col);
    newNodes[1].setRow(row);
    newNodes[0].setCol(col + 1);
    newNodes[0].setRow(row + 1);
    newNodes[0].setCol(col + 1);
    newNodes[0].setRow(row + 1);
    newNodes[0].setCol(col);

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

    //set adjacency to other related positions: 
    //iterate through thenodes already there and if they are at an adjacent position, add adjacency (both ways)
    for (int i = 0; i < mapNodes->size(); i++) {
        //if the node has same row and col as tested, return false 
        int testedRow = mapNodes->at(i)->getRow();
        int testedCol = mapNodes->at(i)->getCol();
        if ((testedRow == row - 1 && testedCol == col) || (testedRow == row && testedCol == col - 1)) {
            newNodes[0].getAdjNodes()->push_back(mapNodes->at(i));
            mapNodes->at(i)->getAdjNodes()->push_back(&(newNodes[0]));
        }
        else if ((testedRow == row - 1 && testedCol == col + 1) || (testedRow == row && testedCol == col + 2)) {
            newNodes[1].getAdjNodes()->push_back(mapNodes->at(i));
            mapNodes->at(i)->getAdjNodes()->push_back(&(newNodes[1]));
        }
        else if ((testedRow == row + 1 && testedCol == col + 2) || (testedRow == row + 2 && testedCol == col + 1)) {
            newNodes[2].getAdjNodes()->push_back(mapNodes->at(i));
            mapNodes->at(i)->getAdjNodes()->push_back(&(newNodes[2]));
        }
        else if ((testedRow == row + 2 && testedCol == col) || (testedRow == row + 1 && testedCol == col - 1)) {
            newNodes[3].getAdjNodes()->push_back(mapNodes->at(i));
            mapNodes->at(i)->getAdjNodes()->push_back(&(newNodes[3]));
        }
    }

    //place in the map
    for (int i = 0; i < 4; i++) {
        (*mapNodes).push_back(&newNodes[i]);
    }

    return newNodes;

}

//checks for out of bounds depending on how many players and checks if there is a tile already there.
//returns true if valid, false if not
bool Map::validPosition(int testedRow, int testedCol) {
    bool validPos = true;
    //first, row and column has to be pair, so that the tile is placed in an actual square
    if (testedRow % 2 == 0 && testedCol % 2 == 0) {
        //check for out of bounds
        if (testedRow < 0 || testedRow>13 || testedCol < 0 || testedCol>13) {
            return false;;
        }
        else if (testedCol == 0 || testedCol == 1 || testedCol == 12 || testedCol == 13) {
            if (*playerNum == 2 || *playerNum == 3) {
                return false;;
            }
            else {
                if (testedRow == 0 || testedRow == 1 || testedRow == 12 || testedRow == 13) return false;
            }
        }
        else if (testedRow == 0 || testedRow == 1 || testedRow == 12 || testedRow == 13) {
            if (*playerNum == 2) {
                return false;
            }
        }
        for (int i = 0; i < mapNodes->size(); i++) {
            //if the node has same row and col as tested, return false 
            if (mapNodes->at(i)->getRow() == testedRow && mapNodes->at(i)->getCol() == testedCol) return false;
        }
        return true;
    }
    else return false;
}

void Map::setMapSize(int playerNumber) {
    if (playerNumber == 2) {
        std::vector<Node*>* emptyMap;
        emptyMap->reserve(100);
        setMapNodes(emptyMap);
    }
    else if (playerNumber == 3) {
        std::vector<Node*>* emptyMap;
        emptyMap->reserve(140);
        setMapNodes(emptyMap);
    }

    else if (playerNumber == 4) {
        std::vector<Node*>* emptyMap;
        emptyMap->reserve(180);
        setMapNodes(emptyMap);
    }
}

std::string Map::getMapSize(int playerNumber) {
    if (playerNumber == 2) {
        return "the center 5x5 area.";
    }
    else if (playerNumber == 3) {
        return "the light center 5x5 area and the top and bottom green squares.";
    }

    else if (playerNumber == 4) {
        return "the entire playing area.";
    }
}

