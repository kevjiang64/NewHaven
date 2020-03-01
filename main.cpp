//
//  main.cpp
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
    Map::Node topLeft = Map::Node(0, {}, false);
    Map::Node topRight = Map::Node(0, {}, false);
    Map::Node bottomRight = Map::Node(1, {}, false);
    Map::Node bottomLeft = Map::Node(2, {}, false);
    Map::Tile playerTile1 = Map::Tile(topLeft,topRight,bottomRight, bottomLeft);

    topLeft.setAdjNodes({topRight,bottomLeft});
    topRight.setAdjNodes({topLeft,bottomRight});
    bottomRight.setAdjNodes({topRight,bottomLeft});
    bottomLeft.setAdjNodes({bottomRight,topLeft});

    std::vector<Map::Node> mapNodes = { topLeft,topRight,bottomRight,bottomLeft };
    gameBoard.setMapNodes = mapNodes;
    gameBoard.setPlayerNumber = playerNumber;



    std::cout << "The number of players in this game is " << playerNumber << ". The game board will use " << gameBoard.getMapSize << "\n";
    std::cout << "The adjacent nodes to the TopRight Node of the tile are: " << topRight.getAdjNodes << "\n";
    
}
