
#include <cstdlib>
#include <vector>

#include "Part6.h"
#include "GBMaps.h"
#include "VGMap.h"
#include "Player.h"
#include "Resources.h"

using namespace std;

/*int main() {
	Player player = *(new Player());
	DeckHarvestTile deckTiles = *(new DeckHarvestTile());
	Map* board = (new Map(2, *(new vector<Map::Node*>)));
	bool tilePlaced = player.placeHarvestTile(0, 2, 2, board, deckTiles);
	tilePlaced = player.placeHarvestTile(1, 2, 4, board, deckTiles);
	tilePlaced = player.placeHarvestTile(0, 4, 2, board, deckTiles);
	tilePlaced = player.placeHarvestTile(1, 4, 4, board, deckTiles);
	

	vector<int> resourceMarkers = *(player.getHand()->getResourceMarkers());
	for (int i = 0; i < 4; i++) {
		cout << "number of resource #" << i << " is " << resourceMarkers.at(i) << endl;
	}

	for (int i = 0; i < player.getBuildings().size(); i++) {
		cout << "player's buildings" << player.getBuildings().at(i).getNumber() << "   " << player.getBuildings().at(i).getLabel() << endl;
	}
	//place a column of 6 buildings and row of 4
	cout << "\nWe fill with buildings the row #2 and the column #2: \nexpected score: 12" << endl;
	player.buildVillage(0, 0, 1);
	player.buildVillage(0, 1, 1);
	player.buildVillage(0, 2, 1);
	player.buildVillage(0, 3, 1);
	player.buildVillage(0, 4, 1);
	player.buildVillage(0, 5, 1);

	for (int i = 0; i < player.getBuildings().size(); i++) {
		cout << "player's buildings" << player.getBuildings().at(i).getNumber() << "   " << player.getBuildings().at(i).getLabel() << endl;
	}

	/*player.buildVillage(1, 3, 0);
	player.buildVillage(0, 3, 1);
	player.buildVillage(0, 3, 2);
	player.buildVillage(0, 3, 3);
	player.buildVillage(0, 3, 4);


	Score score = *(new Score());
	int finalCount = score.countFinalPoints(*(player.getVillageBoard()));
	cout << "final count : " << finalCount << endl;


	return 0;
}*/
