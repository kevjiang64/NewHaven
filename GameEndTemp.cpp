#include <vector>
#include <iostream>
#include "GBMaps.h"
#include "VGMap.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "Player.h"
#include "Resources.h"
#include "Part6.h"

using namespace std;

//returns the index of the player between the ones indicated 
vector<int>* fewestEmptySpaces(vector<Player*>* players, vector<bool>* tied) {
	vector<int>* emptySpaces = new vector<int>(players->size());
	for (int i = 0; i < players->size(); i++) {
		emptySpaces->at(i) = players->at(i)->getVillageBoard()->numberOfEmptySpaces();
	}
	
	int maxScore = 0;
	bool twoMaxScores = false;
	for (int i = 0; i < 4; i++) {
		if (tied->at(i)) {
			if (emptySpaces->at(i) > maxScore) {
				maxScore = emptySpaces->at(i);
				twoMaxScores = false;
			}
			else if (emptySpaces->at(i) == maxScore) {
				twoMaxScores = true;
			}
		}
	}

	if (twoMaxScores) {
		vector<bool>* tiedAgain = new vector<bool>(players->size());
		for (int i = 0; i < players->size(); i++) {
			if (tied->at(i) && emptySpaces->at(i) == maxScore) {
				tiedAgain->at(i) = true;
			}
			else {
				tiedAgain->at(i) = false;
			}
		}
		leastBuildingsLeftOver(players, tiedAgain);
	}
	else {
		int indexWinner = 0;
		while (true) {
			if (tied->at(indexWinner) && emptySpaces->at(indexWinner) == maxScore) {
				vector<int>* indexesWinners = new vector<int>(1);
				indexesWinners->push_back(indexWinner);
				return indexesWinners;
			}
		}
	}
}

vector<int>* leastBuildingsLeftOver(vector<Player*>* players, vector<bool>* tied) {
	vector<int>* buildingsLeftover = new vector<int>(players->size());
	for (int i = 0; i < players->size(); i++) {
		buildingsLeftover->at(i) = players->at(i)->getBuildings()->size(); //I assume that we don't count the numbers... do we?
	}

	int maxScore = 0;
	bool twoMaxScores = false;
	for (int i = 0; i < 4; i++) {
		if (tied->at(i)) {
			if (buildingsLeftover->at(i) > maxScore) {
				maxScore = buildingsLeftover->at(i);
				twoMaxScores = false;
			}
			else if (buildingsLeftover->at(i) == maxScore) {
				twoMaxScores = true;
			}
		}
	}

	if (twoMaxScores) {
		vector<int>* indexesWinners = new vector<int>();
		for (int i = 0; i < players->size(); i++) {
			if (tied->at(i) && buildingsLeftover->at(i) == maxScore) {
				indexesWinners->push_back(i);
			}

		}
		return indexesWinners;
	}
	else {
		int i = 0;
		while (true) {
			if (tied->at(i) && buildingsLeftover->at(i) == maxScore) {
				vector<int>* indexesWinners = new vector<int>();
				indexesWinners->push_back(i);
				return indexesWinners;
			}
		}
	}
}