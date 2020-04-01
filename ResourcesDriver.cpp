#include <stdio.h>
#include "Resources.h"

/*int main() {
    
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
    
     Building newBuilding;
    HarvestTile newHarvestTile;
    cout << "Building: " << endl;
    newBuilding.printBuilding();
    cout << "\n";
    cout << "Harvest Tile: " << endl;
    newHarvestTile.printHarvestTile();

    cout << "\n" << endl;
    vector<int>* resources = new vector<int>(4);
    for (int i = 0; i < 4; i++) {
        resources->at(i) = i;
    }

    Hand hand;
    hand.exchange(*resources);
    hand.printResources();

    return 0;
}*/
