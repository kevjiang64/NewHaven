#include "Player.h"
#include "Resources.h"
#include <vector>
#include "VGMap.h"
#include "GBMaps.h"
#include <iostream>

using namespace std;

int main() {
	cout << "hello" << endl;
	Player player = *(new Player());
	for (int i = 0; i < player.getBuildings().size(); i++) {
		cout << "player's buildings" << player.getBuildings().at(i).getNumber() << endl;
	}

	DeckBuilding deck = *(new DeckBuilding());
	player.drawBuilding(deck);
	cout << "" << endl;
	for (int i = 0; i < player.getBuildings().size(); i++) {
		cout << "player's buildings" << player.getBuildings().at(i).getNumber() << endl;
	}

	cout << "player done" << endl;
	return 0;
}