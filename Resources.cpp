#include "Resources.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

HarvestTile::HarvestTile() {
    topLeft = (int*)malloc(15*sizeof(int));
//    resources = (int*)malloc(20*sizeof(int));

    int wheatCount = 0, sheepCount = 0, timberCount = 0, stoneCount = 0, index = 0;
    resources = new int[4];

    while (index < 4) {
        mt19937 rng;
        rng.seed(random_device()());
        uniform_int_distribution<mt19937::result_type> dist;
        
        int output = dist(rng) % 4;

//        cout << output << endl;
        
        if (index == 0)
            *topLeft = output;

        if ((output == 0 && wheatCount > 3) || (output == 1 && sheepCount > 3) || (output == 2 && timberCount > 3) || (output == 3 && stoneCount > 3))
            continue;

//        myResources[index] = static_cast<ResourceType>(output);
        resources[index] = output;
        index++;

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
    
    for(int i=0;i<4;i++) {
        cout << *(resources+i) << endl;
    }
};

HarvestTile::~HarvestTile() {
	delete topLeft;
    delete[] resources;
};

//void HarvestTile::createHarvestTile(HarvestTile newTile) {
//
//};

DeckHarvestTile::DeckHarvestTile() {
	count = new int(60);
};

DeckHarvestTile::~DeckHarvestTile() {
	delete count;
};

HarvestTile DeckHarvestTile::draw() {
    if (*count <= 0) {
		cout << "There is no harvest tile left." << endl;
        HarvestTile emptyTile;
        emptyTile.setResources(0);
        emptyTile.setTopLeft(0);
        return emptyTile;
    }
    else {
        HarvestTile newTile;
        (*count)--;
        return newTile;
    }
};

Building::Building() {
    int stop = 0;
    label = (int*)malloc(15*sizeof(int));
//    color = (int*)malloc(15*sizeof(int));
    number = (int*)malloc(15*sizeof(int));
    
    mt19937 rng;
    rng.seed(random_device()());
    uniform_int_distribution<mt19937::result_type> dist;
    
    while(!stop) {
        int output = dist(rng) % 4;
        int numberOutput = dist(rng) % 6 + 1;
        
        for(int i=0; i<4;i++) {
            for(int j=0; j<6; j++) {
                if((i == output) && (j == numberOutput-1) && (count[i][j] > 6))
                    continue;
            }
        }
    
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
    
    cout << *number;
};

Building::~Building() {
	delete label;
    delete number;
};

//void Building::createBuilding(Building newBuilding) {
//
//};

DeckBuilding::DeckBuilding() {
	totalCount = new int(144);
    count = new int[24];
};

DeckBuilding::~DeckBuilding() {
	delete totalCount;
    delete count;
};

Building* DeckBuilding::draw(int num) {
    Building* ptr;
    
    
    if (*totalCount <= 0) {
		cout << "There is no building left." << endl;
        ptr = nullptr;
    }

    else {
        Building buildingsCreated[num];
        ptr = buildingsCreated;
    }
    return ptr;
};


int main() {
    DeckBuilding myDeck;
    return 0;
}
