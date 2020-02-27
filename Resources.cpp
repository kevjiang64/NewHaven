#include "Resources.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

// HARVEST TILE

HarvestTile::HarvestTile() {
    topLeft = (int*)malloc(15*sizeof(int));
    resources = new int[4];
    
    //create counts to keep track of the resources (limited to 3 per harvest tiles)
    int wheatCount = 0, sheepCount = 0, timberCount = 0, stoneCount = 0, index = 0;

    while (index < 4) {
        
        //generate random numbers for the resources
        mt19937 rng;
        rng.seed(random_device()());
        uniform_int_distribution<mt19937::result_type> dist;
        
        int output = dist(rng) % 4;
        
        if (index == 0)
            *topLeft = output;

        if ((output == 0 && wheatCount > 3) || (output == 1 && sheepCount > 3) || (output == 2 && timberCount > 3) || (output == 3 && stoneCount > 3))
            continue;

        resources[index] = output;
        index++;

        //add resource to the count
        switch (output) {
            case 0:
                wheatCount++;
                continue;
            case 1:
                sheepCount++;
                continue;
            case 2:
                timberCount++;
                continue;
            case 3:
                stoneCount++;
                continue;
            default:
                break;
        }
    }
};

HarvestTile::~HarvestTile() {
	delete topLeft;
    delete[] resources;
};

//DECK FOR HARVEST TILES

DeckHarvestTile::DeckHarvestTile() {
	count = new int(60);
};

DeckHarvestTile::~DeckHarvestTile() {
	delete count;
};

HarvestTile DeckHarvestTile::draw() {
    HarvestTile newTile;
    
    if (*count <= 0) {
		cout << "There is no harvest tile left." << endl;
        
        //set everything to 0 to return an empty tile
        newTile.setResources(0);
        newTile.setTopLeft(0);
    }
    
    else {
        (*count)--;
    }
    
    return newTile;
};

// BUILDING

Building::Building() {
    int stop = 0;
    
    //allocate memory (??) for label and number
    label = (int*)malloc(15*sizeof(int));
    number = (int*)malloc(15*sizeof(int));
    
    //generate random numbers
    mt19937 rng;
    rng.seed(random_device()());
    uniform_int_distribution<mt19937::result_type> dist;
    
    while(!stop) {
        //generate random numbers for the creation of the building
        int output = dist(rng) % 4;
        int numberOutput = dist(rng) % 6 + 1;
        
        //keep track of the limit of buildings created
        for(int i=0; i<4;i++) {
            for(int j=0; j<6; j++) {
                if((i == output) && (j == numberOutput-1) && (count[i][j] > 6))
                    continue;
            }
        }
        
        //add the building created to the count
        for(int i=0; i<4;i++) {
            for(int j=0; j<6; j++) {
                if((i == output) && (j == numberOutput-1))
                    count[i][j]++;
            }
        }
        
        *label = output;
        *number = numberOutput;
        stop = 1;
    }
};

Building::~Building() {
	delete label;
    delete number;
};

DeckBuilding::DeckBuilding() {
	totalCount = new int(144);
    count = new int[24];
};

DeckBuilding::~DeckBuilding() {
	delete totalCount;
    delete count;
};

Building DeckBuilding::draw() {
    Building newBuilding;
    
    if (*totalCount <= 0) {
		cout << "There is no building left." << endl;
        newBuilding.setLabel(-1);
        newBuilding.setNumber(-1);
    }
    
    else {
        (*totalCount)--;
    }
    
    return newBuilding;
};


int main() {
    DeckBuilding myDeck;
    return 0;
}
