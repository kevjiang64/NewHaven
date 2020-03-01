#include "Player.h"
#include "Resources.h"
#include <vector>
#include "VGMap.h"
#include "GBMaps.h"
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

	Map board = *(new Map(0, *(new vector<Map::Node>)));

	bool tilePlaced = player.placeHarvestTile(0, board, deckTiles);
	
	cout << "" << endl;
	cout << "player done" << endl;
	return 0;
}