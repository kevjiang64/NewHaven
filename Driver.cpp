#include <stdio.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <fstream>
#include <regex>
#include <conio.h>
#include <cstdlib>
#include <vector>
#include "GBMaps.h"
#include "VGMap.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "Player.h"
#include "Resources.h"
#include "Part6.h"

int main() {
    
    //PART 1
    /*
    bool count = true;
    int playerNumber;

    while (count == true) {
        std::cout << "How many players would you like to play with?" << "\n";
        std::cin >> playerNumber;
        if (playerNumber != 2 && playerNumber != 3 && playerNumber != 4)
            std::cout << "This is an invalid number of players. Please choose either 2,3 or 4 players." << "\n";
        else
            count = false;
    }

    //create an empty map with number of nodes corresponding with the appropriate number of players
    Map gameBoard;
    gameBoard.setMapSize(playerNumber);


    //instantiate nodes of a tile and create a tile object containing the nodes
    Map::Node* topLeft = new Map::Node(0, {}, false);
    Map::Node* topRight = new Map::Node(0, {}, false);
    Map::Node* bottomRight = new Map::Node(1, {}, false);
    Map::Node* bottomLeft = new Map::Node(2, {}, false);
    //Map::Tile* playerTile1 = new Map::Tile(topLeft, topRight, bottomRight, bottomLeft);

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

    std::cout << "The number of players in this game is " << playerNumber << ". The game board will use " << gameBoard.getMapSize(playerNumber) << "\n";
    std::cout << "The adjacent nodes to the TopRight Node of the tile are: " << topRight->getAdjNodes() << "\n";
    std::cout << "The valid game board is a connected graph: " << gameBoard.testConnected() << endl;
    */
    //PART 2
    /*
    //Creating valid/invalid cases of VGMaps
    //First
    string answer = "yes";

    while (answer == "yes")
    {
        int row;
        int col;
        cout << "What will be the value of the row?\n";
        cin >> row;
        cout << "What will be the value of the col?\n";
        cin >> col;
        VGMap a = VGMap(row, col);

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                VGMap::Node node = a.getBoard()[i][j];
                
                cout << "Number of adjacent nodes at position (" << i << "," << j << ")" << " :" << node.getSize() << "\n";
            }
        }
        cout << "Do you want to test again?";
        cin >> answer;
    }
    */
    //PART 3
    /*
    //GB Map Loader Driver
    
    int numOfPlayers;
    std::vector<Map::Node*> initTile;

    cout << "Test 1:\n";
    //Checking if a VGMap is valid or invalid
    if (checkFile("validMap.txt"))
    {
        numOfPlayers = checkValidPlayerNum("validMap.txt");
        initTile = checkValidTile("validMap.txt");
        cout << "The Number of Players is : " << numOfPlayers << "\n";
        if (numOfPlayers == 2 || numOfPlayers == 3 || numOfPlayers == 4)
        {
            cout << "A GBMapLoader Object with a GBMaps Object will be created\n\n";
            GBMapLoader newMap = GBMapLoader(numOfPlayers, initTile);
        }
    }

    cout << "Test 2\n";
    //Checking if a VGMap is valid or invalid
    if (checkFile("invalidMap.txt"))
    {
        numOfPlayers = checkValidPlayerNum("invalidMap.txt");
        initTile = checkValidTile("invalidMap.txt");
        if (numOfPlayers == 0)
        {
            cout << "A GBMapLoader Object will not be created\n";
        }
    }
    */
    //VG Map Loader Driver
    /*
    int row;
    int column;

    cout << "Test 1:\n";
    //Checking if a VGMap is valid or invalid
    if (fexists("valid.txt"))
    {
        row = checkValidRow("valid.txt");
        column = checkValidColumn("valid.txt");
        cout << "The Row Value is : " << row <<"\n";
        cout << "The Column Value is : " << column<<"\n";
        if (row == 6 && column == 5)
        {
            cout << "A VGMapLoader Object with a VGMap Object will be created\n\n";
            VGMapLoader a = VGMapLoader(row, column);
        }
    }

    cout << "Test 2\n";
    //Checking if a VGMap is valid or invalid
    if (fexists("invalid.txt"))
    {
        int row = checkValidRow("invalid.txt");
        int column = checkValidColumn("invalid.txt");
        if (row == 0 && column == 0)
        {
            cout << "A VGMapLoader Object will not be created\n";
        }
    }
    */
    //PART 4
    /*
    cout << "player start" << endl;
    cout << "" << endl;
    Player player = *(new Player());
    
    //output buildings
    for (int i = 0; i < player.getBuildings().size(); i++) {
        cout << "player's buildings " << player.getBuildings().at(i).getNumber() << endl;
    }
    cout << "" << endl;
    //output tiles
    for (int i = 0; i < player.getTiles().size(); i++) {
        cout << "player's tiles ";
        for (int j = 0; j < 4; j++) {
            cout << (player.getTiles().at(i).getResources()[j]) << " ";
        }
        cout << " - top left at index: " << *(player.getTiles().at(i).getTopLeft()) << endl;
    }
    cout << "" << endl;
    //draw Building
    DeckBuilding deckBuilding = *(new DeckBuilding());
    player.drawBuilding(deckBuilding);
    for (int i = 0; i < player.getBuildings().size(); i++) {
        cout << "player's buildings" << player.getBuildings().at(i).getNumber() << endl;
    }
    cout << "" << endl;
    //place harvest tile
    DeckHarvestTile deckTiles = *(new DeckHarvestTile());
    Map* board = (new Map(2, *(new vector<Map::Node*>)));
    bool tilePlaced = player.placeHarvestTile(0, 2, 2, board, deckTiles);
    cout << "" << endl;
    player.resourceTracker();
    cout << "\n" << endl;
    for (int i = 0; i < player.getTiles().size(); i++) {
        cout << "player's tiles ";
        for (int j = 0; j < 4; j++) {
            cout << (player.getTiles().at(i).getResources()[j]) << " ";
        }
        cout << " - top left at index: " << *(player.getTiles().at(i).getTopLeft()) << endl;
    }
    cout << "" << endl;
    
    
    cout << "" << endl;
    cout << "player done" << endl;
    */
    //PART 5
    /*
    DeckHarvestTile newDeck1;
    
    cout << "A new deck of Harvest Tiles has been created" << endl;
    
    HarvestTile newHarvestTile = newDeck1.draw();
    
    cout << "A harvest tile has been drawn from the deck of Harvest tiles:" << endl;
    cout << "\tResources of the harvest tile: ";
    
    for(int i = 0; i<4; i++) {
        int value = newHarvestTile.getResources()[i];
        
        switch(value) {
            case 0:
                cout << "Wheat ";
                continue;
            case 1:
                cout << "Sheep ";
                continue;
            case 2:
                cout << "Timber ";
                continue;
            case 3:
                cout << "Stone ";
                continue;
            default:
                break;
        };
    }
    
    DeckBuilding newDeck2;
    
    cout << "\n\nA new deck of Buildings has been created" << endl;
    
    Building newBuilding = newDeck2.draw();
    
    cout << "A building has been drawn from the deck of Buildings:" << endl;
    cout << "\tColor of the building: ";
    
    int color = newBuilding.getLabel();
    
    switch (color) {
        case 0:
            cout << "Green" << endl;
            break;
            
        case 1:
            cout << "Gray" << endl;
            break;
            
        case 2:
            cout << "Red" << endl;
            break;
            
        case 3:
            cout << "Yellow" << endl;
            break;
            
        default:
            break;
    }
    
    cout << "\tLabel of the building: ";
    
    int label = newBuilding.getLabel();
    
    switch (label) {
        case 0:
            cout << "Meadow" << endl;
            break;
            
        case 1:
            cout << "Quarry" << endl;
            break;
            
        case 2:
            cout << "Forest" << endl;
            break;
            
        case 3:
            cout << "Wheatfield" << endl;
            break;
            
        default:
            break;
    }
    
    cout << "\tNumber of the building: ";
    cout << newBuilding.getNumber() << endl;
    
    bool flipped = newBuilding.isFlipped();
    cout << "\tHas the building been flipped: ";
    flipped ? cout << "yes" << endl : cout << "no" << endl;
    */
    //PART 6
    //*
    Player player = *(new Player());
    DeckHarvestTile deckTiles = *(new DeckHarvestTile());
    Map* board = (new Map(2, *(new vector<Map::Node*>)));
    bool tilePlaced = player.placeHarvestTile(0, 2, 2, board, deckTiles);

    vector<int> resourceMarkers = *(player.getHand()->getResourceMarkers());
    for (int i = 0; i < 4; i++) {
        cout << "number of resource #" << i << " is " << resourceMarkers.at(i) << endl;
    }

    //place a column of 6 buildings and row of 4
    cout << "\nWe fill with buildings the row #2 and the column #2: \nexpected score: 12" << endl;
    player.buildVillage(0, 0, 1);
    player.buildVillage(1, 1, 1);
    player.buildVillage(2, 2, 1);
    player.buildVillage(3, 3, 1);
    player.buildVillage(4, 4, 1);
    player.buildVillage(5, 5, 1);

    player.buildVillage(1, 4, 0);
    player.buildVillage(2, 4, 1);
    player.buildVillage(3, 4, 2);
    player.buildVillage(4, 4, 3);
    player.buildVillage(5, 4, 4);


    Score score = *(new Score());
    int finalCount = score.countFinalPoints(*(player.getVillageBoard()));
    cout << "final count : " << finalCount << endl;
    
    return 0;
    //*/
}
