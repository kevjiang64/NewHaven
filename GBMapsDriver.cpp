//
//  GBMapsDriver.cpp
//  COMP345_A1
//
//  Created by Justin Teixeira on 2020-02-10.
//  Copyright © 2020 Justin Teixeira. All rights reserved.
//

#include <iostream>
#include "GBMaps.h"

int main() {
    bool count = true;
    int playerNumber;

    while (count == true) {
        std::cout << "How many players would you like to play with?" << "\n";
        std::cin >> playerNumber;
        if (playerNumber != 2 || playerNumber != 3 || playerNumber != 4)
            std::cout << "This is an invalid number of players. Please choose either 2,3 or 4 players." << "\n";
        else
            count == false;
    }

    //create an empty map with number of nodes corresponding with the appropriate number of players
    Map gameBoard;
    gameBoard.setMapSize(playerNumber);


    //instantiate nodes of a tile and create a tile object containing the nodes
    Map::Node* topLeft = new Map::Node(0, {}, false);
    Map::Node* topRight = new Map::Node(0, {}, false);
    Map::Node* bottomRight = new Map::Node(1, {}, false);
    Map::Node* bottomLeft = new Map::Node(2, {}, false);
    Map::Tile* playerTile1 = new Map::Tile(topLeft, topRight, bottomRight, bottomLeft);

    std::vector<Map::Node*>* topLeftAdj = new std::vector<Map::Node*>();
    topLeftAdj->push_back(topRight);
    topLeftAdj->push_back(bottomLeft);
    topLeft->setAdjNodes(topLeftAdj);

    std::vector<Map::Node*>* topRightAdj = new std::vector<Map::Node*>();
    topRightAdj->push_back(topLeft);
    topRightAdj->push_back(bottomRight);
    topRight->setAdjNodes(topRightAdj);

    std::vector<Map::Node*>* bottomLeftAdj = new std::vector<Map::Node*>();
    bottomLeftAdj->push_back(topLeft);
    bottomLeftAdj->push_back(bottomRight);
    bottomLeft->setAdjNodes(bottomLeftAdj);

    std::vector<Map::Node*>* bottomRightAdj = new std::vector<Map::Node*>();
    bottomRightAdj->push_back(topRight);
    bottomRightAdj->push_back(bottomLeft);
    bottomRight->setAdjNodes(bottomRightAdj);

    std::vector<Map::Node*>* mapNodes = new std::vector<Map::Node*>();
    mapNodes->push_back(topLeft);
    mapNodes->push_back(topRight);
    mapNodes->push_back(bottomRight);
    mapNodes->push_back(bottomLeft);

    gameBoard.setMapNodes(mapNodes);
    gameBoard.setPlayerNumber(&playerNumber);




    std::cout << "The number of players in this game is " << playerNumber << ". The game board will use " << gameBoard.getMapSize << "\n";
    std::cout << "The adjacent nodes to the TopRight Node of the tile are: " << topRight->getAdjNodes << "\n";
    std::cout << "The valid game board is a connected graph: " << gameBoard.testConnected << endl;

}
