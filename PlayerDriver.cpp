#include "Player.h"
#include "Resources.h"
#include <vector>
#include "VGMap.h"
#include "GBMaps.h"
#include "Part6.h"
#include <iostream>

using namespace std;

int main() {
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

	Map* board = (new Map(2, *(new vector<Map::Node*>)));

	/*bool tilePlaced = player.placeHarvestTile(0, 2, 2, board, deckTiles);
	//ca plante ici
	cout << "playernum dans le main " << *(board->getPlayerNum()) << endl;
	cout << "row dans le main " << ((*board->getMapNodes())[0]->getRow()) << endl;
	vector<int> resourceMarkers = *(player.getHand()->getResourceMarkers());
	for (int i = 0; i < 4;  i++) {
		cout << "number of resource #" << i << " is " << resourceMarkers.at(i) << endl;
	}
	
	
	tilePlaced = player.placeHarvestTile(0, 4, 2, board, deckTiles);
	resourceMarkers = *(player.getHand()->getResourceMarkers());
	for (int i = 0; i < 4; i++) {
		cout << "number of resource #" << i << " is " << resourceMarkers.at(i) << endl;
	}*/


	
	cout << "" << endl;
	cout << "player done" << endl;
	return 0;
}