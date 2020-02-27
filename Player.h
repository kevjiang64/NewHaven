//
//  Player.h
//  Player
//
//  Created by Arianne Chau on 2020-02-11.
//  Copyright © 2020 Arianne Chau. All rights reserved.
//

#include <vector>
#include "VGMap.h"
#ifndef Player_h
#define Player_h


class Player {
    private:
        VGMap* vb;
        std::vector<Building>* buildings;
        std::vector<HarvestTile>* tiles;
        std::vector<int>* resourceMarkers;
		bool canBuild(VGMap vboard, Building building, VGMap::Node pos);
    
    public:
		Player();
        bool placeHarvestTile(HarvestTile tile, Position pos);
        void drawBuilding();
        void drawHarvestTile();
        resourceTracker();
		void calculateResources(GameBoard board, GraphNodes* nodesJustPlaced);
		bool buildVillage(int buildingIndex, VGNode position);


}

#endif /* Player_h */
