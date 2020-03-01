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
    VGMap* vb;
    vector<Building>* buildings;
    vector<HarvestTile>* tiles;
    vector<int>* resourceMarkers;
    bool canBuild(VGMap vboard, Building building, VGMap::Node pos);

public:
    Player();
    ~Player();
    bool placeHarvestTile(int noTile, Map board, DeckHarvestTile deck);
    void drawBuilding(DeckBuilding deckBuilding);
    void drawHarvestTile(DeckHarvestTile deck, int no);
    void resourceTracker();
    void calculateResources(Map board, vector<Map::Node> nodesJustPlaced);
    bool buildVillage(int buildingIndex, int row, int col);
    //getters
    vector<Building> getBuildings() { return *buildings; };
    vector<HarvestTile> getTiles() { return *tiles; };
    vector<int> getResourceMarkers() { return *resourceMarkers;  };
    
};

#endif /* Player_h */
