#include <vector>
#include <iostream>
#include "GBMaps.h"
#include "VGMap.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "Player.h"
#include "Resources.h"
#include "Part6.h"
#include "GameEnd.h"


//Method to check if the game is finished and outputs the results
void gameTie(Map* gameMap, vector<Player*>* players) {
        int* scores = new int[players->size()];

        //fill up the array of scores
        for (int i = 0; i < players->size(); i++) {
            scores[i] = players->at(i)->getVillageBoard()->getPoints();
        }

        //find the max score of the players in the score array
        int max = scores[0];
        for (int i = 1; i < players->size(); i++) {
            if (scores[i] > max) {
                max = scores[i];
            }
        }

        //check if there is a tie
        int count = 0;
        vector<Player*>* tiedPlayers = new vector<Player*>(players->size());
        vector<bool>* tied = new vector<bool>(players->size());
        for (int i = 0; i < players->size(); i++) {
            if (max == scores[i]) {
                count++;
                tiedPlayers->at(i) = players->at(i);
            }
        }
        //if there is a tie enter this
        if (count >= 2) {
            vector<int>* winner = new vector<int>();
            winner = fewestEmptySpaces(tiedPlayers, tied);

            //displays the winner/winners (in case of a shared win)
            cout << "The winner is: ";
            for (int i = 0; i < winner->size(); i++) {
                cout << players->at(winner->at(i))->getID() << endl;
            }
        }

        //no tie; displays the winner, and their points
        else {
            cout << "The winner is: ";
            for (int i = 0; i < players->size(); i++) {
                if (max == players->at(i)->getVillageBoard()->getPoints()) {
                    cout << players->at(i)->getID() << endl;
                }
            }
            cout << "With " << max << "points!" << endl;
        }
 
   
}

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

int GameEndDriver() {

    Map* gameMap = new Map();
    vector<Map::Node*>* mapNodes = new vector<Map::Node*>(96);
    gameMap->setMapNodes(mapNodes);

    vector<Player*>* playerVector = new vector<Player*>();

    Player* player1 = new Player();
    Player* player2 = new Player();


    player1->getVillageBoard()->build(new Building(), 3, 1);
    player1->getVillageBoard()->build(new Building(), 3, 2);
    player1->getVillageBoard()->build(new Building(), 3, 3);
    player1->getVillageBoard()->build(new Building(), 3, 4);
    player1->getVillageBoard()->build(new Building(), 3, 5);

    player2->getVillageBoard()->build(new Building(), 2, 1);
    player2->getVillageBoard()->build(new Building(), 2, 2);
    player2->getVillageBoard()->build(new Building(), 2, 3);
    player2->getVillageBoard()->build(new Building(), 2, 4);
    player2->getVillageBoard()->build(new Building(), 2, 5);

    playerVector->push_back(player1);
    playerVector->push_back(player2);

    gameTie(gameMap, playerVector);


    return 0;
}
