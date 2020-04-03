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
            *topLeft = 0;

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
    
    string firstResourceChar;
    switch (resources[0])
    {
    case 0: firstResourceChar = "M";
        break;
    case 1: firstResourceChar = "Q";
        break;
    case 2: firstResourceChar = "F";
        break;
    case 3: firstResourceChar = "W";
        break;
    }
    string secondResourceChar;
    switch (resources[1])
    {
    case 0: secondResourceChar = "M";
        break;
    case 1: secondResourceChar = "Q";
        break;
    case 2: secondResourceChar = "F";
        break;
    case 3: secondResourceChar = "W";
        break;
    }
    cout << "|" << firstResourceChar << " " << secondResourceChar << "|" << endl;
    switch (resources[3])
    {
    case 0: firstResourceChar = "M";
        break;
    case 1: firstResourceChar = "Q";
        break;
    case 2: firstResourceChar = "F";
        break;
    case 3: firstResourceChar = "W";
        break;
    }
    switch (resources[2])
    {
    case 0: secondResourceChar = "M";
        break;
    case 1: secondResourceChar = "Q";
        break;
    case 2: secondResourceChar = "F";
        break;
    case 3: secondResourceChar = "W";
        break;
    }
    cout << "|" << firstResourceChar << " " << secondResourceChar << "|" << endl;
    cout << "" << endl;
}

void HarvestTile::completeDisplay() {
    cout << "Resources of the harvest tile: ";

    for (int i = 0; i < 4; i++) {
        int value = this->getResources()[i];

        switch (value) {
        case 0:
            cout << "Meadow ";
            continue;
        case 1:
            cout << "Quarry ";
            continue;
        case 2:
            cout << "Forest ";
            continue;
        case 3:
            cout << "Wheatfield ";
            continue;
        default:
            cout << "empty ";
            continue;
        };
    }
}
// DECK FOR HARVEST TILES

DeckHarvestTile::DeckHarvestTile() {
	count = new int(0);
    allTiles = new HarvestTile[60];
    
    //create 60 tiles at the beginning
    for (int i=0; i<60; i++) {
        HarvestTile tile;
        allTiles[i] = tile;
    }
};

DeckHarvestTile::~DeckHarvestTile() {
	//delete count;
};

HarvestTile DeckHarvestTile::draw() {
    
    if (*count >= 60) {
		cout << "There is no harvest tile left." << endl;
        HarvestTile emptyTile;
        
        //set everything to -1 and return an empty tile
        for (int i=0; i<4; i++) {
             emptyTile.setResources(-1, i);
        }
        emptyTile.setTopLeft(-1);
        return emptyTile;
    }
    
    else {
        (*count)++;
    }
    
    return allTiles[(*count)-1];
};

// BUILDING

Building::Building() {
	//allocate memory (??) for label and number
    label = (int*)malloc(15*sizeof(int));
    number = (int*)malloc(15*sizeof(int));
	
    
	flipped = (bool*)malloc(sizeof(bool));
    used = (bool*)malloc(sizeof(bool));
	*flipped = false;
    *used = false;
};

Building::~Building() {
	//delete label;
    //delete number;
	//delete flipped;
    //delete used;
};

void Building::display() {
    int label = this->getLabel();

    switch (label) {
    case 0:
        cout << "Meadow\t\t";
        break;

    case 1:
        cout << "Quarry\t\t";
        break;

    case 2:
        cout << "Forest\t\t";
        break;

    case 3:
        cout << "Wheatfield\t";
        break;

    default:
        cout << "Empty\t\t";
        break;
    }

    cout << this->getNumber() << endl;

}

void Building::completeDisplay() {
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
        cout << "Empty" << endl;
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
        cout << "Empty" << endl;
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
	totalCount = new int(0);
    count = new int*[4];
	
	for (int i = 0; i < 4; i++) {
		count[i] = new int[6];
	}
    
    allBuildings = new Building*[144];
    
    //create 144 buildings at the beginning
    for (int i=0; i<144; i++) {
        Building* building = new Building();
        
        if(i < 6) {
            building->setLabel(0);
            building->setNumber(1);
        }
        
        if((i>=6) && (i<12)) {
            building->setLabel(0);
            building->setNumber(2);
        }
        
        if((i>=12) && (i<18)) {
            building->setLabel(0);
            building->setNumber(3);
        }
        
        if((i>=18) && (i<24)) {
            building->setLabel(0);
            building->setNumber(4);
        }
        
        if((i>=24) && (i<30)) {
            building->setLabel(0);
            building->setNumber(5);
        }
        
        if((i>=30) && (i<36)) {
            building->setLabel(0);
            building->setNumber(6);
        }
        
        if((i>=36) && (i<42)) {
            building->setLabel(1);
            building->setNumber(1);
        }
        
        if((i>=42) && (i<48)) {
            building->setLabel(1);
            building->setNumber(2);
        }
        
        if((i>=48) && (i<54)) {
            building->setLabel(1);
            building->setNumber(3);
        }
        
        if((i>=54) && (i<60)) {
            building->setLabel(1);
            building->setNumber(4);
        }
        
        if((i>=60) && (i<66)) {
            building->setLabel(1);
            building->setNumber(5);
        }
        
        if((i>=66) && (i<72)) {
            building->setLabel(1);
            building->setNumber(6);
        }
        
        if((i>=72) && (i<78)) {
            building->setLabel(2);
            building->setNumber(1);
        }
        
        if((i>=78) && (i<84)) {
            building->setLabel(2);
            building->setNumber(2);
        }
        
        if((i>=84) && (i<90)) {
            building->setLabel(2);
            building->setNumber(3);
        }
        
        if((i>=90) && (i<96)) {
            building->setLabel(2);
            building->setNumber(4);
        }
        
        if((i>=96) && (i<102)) {
            building->setLabel(2);
            building->setNumber(5);
        }
        
        if((i>=102) && (i<108)) {
            building->setLabel(2);
            building->setNumber(6);
        }
        
        if((i>=108) && (i<114)) {
            building->setLabel(3);
            building->setNumber(1);
        }
        
        if((i>=114) && (i<120)) {
            building->setLabel(3);
            building->setNumber(2);
        }
        
        if((i>=120) && (i<126)) {
            building->setLabel(3);
            building->setNumber(3);
        }
        
        if((i>=126) && (i<132)) {
            building->setLabel(3);
            building->setNumber(4);
        }
        
        if((i>=132) && (i<138)) {
            building->setLabel(3);
            building->setNumber(5);
        }
        
        if((i>=138) && (i<144)) {
            building->setLabel(3);
            building->setNumber(6);
        }
        allBuildings[i] = building;
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

Building* DeckBuilding::draw() {
    if (*totalCount >= 144) {
		cout << "There is no building left." << endl;
		
		Building* emptyBuilding = new Building();
		emptyBuilding->setLabel(-1);
        emptyBuilding->setNumber(-1);
		return emptyBuilding;
    }
    
    else {
        (*totalCount)++;
        
        mt19937 rng;
        rng.seed(random_device()());
        uniform_int_distribution<mt19937::result_type> dist;

        int index = dist(rng) % 144;
        
        while(allBuildings[index]->getUsed() == true) {
            index = dist(rng) % 144;
        }
        
        allBuildings[index]->setUsed(true);
        
        return allBuildings[index];
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
    cout << "\nResources:\nMeadow: " << (*resourceMarkers).at(0) << "\nQuarry: " << (*resourceMarkers).at(1) << "\nForest: " << (*resourceMarkers).at(2) << "\nWheatfield:" << (*resourceMarkers).at(3) << endl;
}

void Hand::resetResourceMarkers() {
    for (int i = 0; i < 4; i++) {
        resourceMarkers->at(i) = 0;
    }
}
