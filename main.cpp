//
//  main.cpp
//  COMP345_A1
//
//  Created by Justin Teixeira on 2020-02-10.
//  Copyright © 2020 Justin Teixeira. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <conio.h>
#include "GBMaps.h"
#include "VGMap.h"
#include "VGMapLoader.h"
#include "Player.h"
#include "Resources.h"


int main() {
    //PART 1
    
    
    
    //PART 2
    
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
    
    //PART 3
    
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
    
    //part 4
    
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
        cout << "player's tiles " << *(player.getTiles().at(i).getTopLeft()) << endl;
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

    Map board = *(new Map(0, *(new vector<Map::Node>)));

    bool tilePlaced = player.placeHarvestTile(0, board, deckTiles);
    
    cout << "" << endl;
    cout << "player done" << endl;
    
    //PART 5
    
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
    
    //PART 6
    
    
    return 0;
}
