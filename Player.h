//
//  Player.h
//  Player
//
//  Created by Arianne Chau on 2020-02-11.
//  Copyright © 2020 Arianne Chau. All rights reserved.
//

#include <vector>
#include "VGMap.h"
#include "Resources.h"
#include "GBMaps.h"
#include "Part6.h"
#ifndef Player_h
#define Player_h


class Player {
private:
    int* id;
    static int* currentId;
    VGMap* vb;
    vector<Building>* buildings;
    vector<HarvestTile>* tiles;
    Hand* hand;
    bool* shipmentTileUsed;
    bool canBuild(VGMap vboard, Building building, VGMap::Node pos);
    bool placeShipmentTile(int row, int col, Map* board, DeckHarvestTile deck);


public:
    Player();
    ~Player();
    bool placeHarvestTile(int noTile, int row, int col, Map* board, DeckHarvestTile deck);
    void drawBuilding(DeckBuilding deckBuilding);
    void drawHarvestTile(DeckHarvestTile deck, int no);
    void resourceTracker();
    void calculateResources(Map board);
    bool buildVillage(int buildingIndex, int row, int col);
    void displayState();
    //getters
    vector<Building> getBuildings() { return *buildings; };
    vector<HarvestTile> getTiles() { return *tiles; };
     Hand* getHand() { return hand;  };
     VGMap* getVillageBoard() { return vb; };
     //setters
     void setVillageBoard(VGMap* board) { vb = board; };
    
};


#endif /* Player_h */
