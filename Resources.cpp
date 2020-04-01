#include "Resources.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

// HARVEST TILE

HarvestTile::HarvestTile() {
    topLeft = (int*)malloc(2*sizeof(int));
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

        if ((output == 0 && wheatCount >= 3) || (output == 1 && sheepCount >= 3) || (output == 2 && timberCount >= 3) || (output == 3 && stoneCount >= 3))
            continue;
        
        if(index == 3) {
            bool ok = false;
            for (int i = 0; i<3; i++) {
                if (output == resources[i])
                    ok = true;
            }
            
            if (wheatCount > 1 || sheepCount > 1 || timberCount > 1 || stoneCount > 1)
            ok = true;
            
            if (!ok)
                continue;
        }

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
	//delete topLeft;
    //delete[] resources;
};

void HarvestTile::display() {
    cout << "Resources of the harvest tile: ";
    
    for(int i = 0; i<4; i++) {
        int value = this->getResources()[i];
        
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
}

// DECK FOR HARVEST TILES

DeckHarvestTile::DeckHarvestTile() {
	count = new int(60);
};

DeckHarvestTile::~DeckHarvestTile() {
	//delete count;
};

HarvestTile DeckHarvestTile::draw() {
    HarvestTile newTile;
    
    if (*count <= 0) {
		cout << "There is no harvest tile left." << endl;
        
        //set everything to -1 and return an empty tile
        newTile.setResources(-1);
        newTile.setTopLeft(-1);
    }
    
    else {
        (*count)--;
    }
    
    return newTile;
};

// BUILDING

Building::Building() {
	//allocate memory (??) for label and number
    label = (int*)malloc(15*sizeof(int));
    number = (int*)malloc(15*sizeof(int));
	
    
	flipped = (bool*)malloc(sizeof(bool));
	*flipped = false;

    //generate random numbers
    mt19937 rng;
    rng.seed(random_device()());
    uniform_int_distribution<mt19937::result_type> dist;

    int output = dist(rng) % 4;
    int numberOutput = dist(rng) % 6 + 1;
        
    *label = output;
    *number = numberOutput;
};

Building::~Building() {
	//delete label;
    //delete number;
	//delete flipped;
};

void Building::display() {
    cout << "Color of the building: ";
    
    int color = this->getLabel();
    
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
    
    cout << "Label of the building: ";
    
    int label = this->getLabel();
    
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
    
    cout << "Number of the building: ";
    cout << this->getNumber() << endl;
    
    bool flipped = this->isFlipped();
    cout << "Flipped?: ";
    flipped ? cout << "yes" << endl : cout << "no" << endl;
}

// DECK OF BUILDINGS

DeckBuilding::DeckBuilding() {
	totalCount = new int(144);
    count = new int*[4];
	
	for (int i = 0; i < 6; i++) {
		count[i] = new int[6];
	}
};

DeckBuilding::~DeckBuilding() {
	//delete totalCount;
    //delete count;
};

//keep track of the limit of buildings created
bool DeckBuilding::validBuilding(Building b) {
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<6; j++) {
			if ((i == b.getLabel()) && (j == b.getNumber() - 1) && (count[i][j] > 6)) {
				return false;
			}
		}
	}

	return true;
};

Building DeckBuilding::draw() {
    if (*totalCount <= 0) {
		cout << "There is no building left." << endl;
		
		Building emptyBuilding;
		emptyBuilding.setLabel(-1);
        emptyBuilding.setNumber(-1);
		return emptyBuilding;
    }
    
    else {
		while (1) {
			Building newBuilding;

			if (validBuilding(newBuilding)) {
				for (int i = 0; i<4; i++) {
					for (int j = 0; j<6; j++) {
						if ((i == newBuilding.getLabel()) && (j == newBuilding.getNumber() - 1)) {
							count[i][j]++;
							break;
						}
					}
				}

				(*totalCount)--;
				return newBuilding;
			}
		}
    }
};

// HAND

Hand::Hand() {
    resourceMarkers = new vector<int>;

    for (int i = 0; i < 4; i++) {
        (*resourceMarkers).push_back(0);
    }
}

Hand::~Hand() {
	
}

void Hand::exchange(vector<int> resources) {
    for (int i = 0; i < 4; i++) {
        (*resourceMarkers)[i] = resources.at(i);
    }
}

void Hand::printResources() {
    cout << "Resources:\nWheat: " << (*resourceMarkers).at(0) << "\nSheep: " << (*resourceMarkers).at(1) << "\nTimber: " << (*resourceMarkers).at(2) << "\nStone:" << (*resourceMarkers).at(3);
}

void Hand::resetResourceMarkers() {
    for (int i = 0; i < 4; i++) {
        resourceMarkers->at(i) = 0;
    }
}
