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
void gameTie(vector<Player*>* players) {

    int* scores = new int[players->size()];

    //fill up the array of scores
    for (int i = 0; i < players->size(); i++) {
        scores[i] = players->at(i)->getVillageBoard()->countPoints();
    }

    //find the max score of the players in the score array
    int max = scores[0];
    for (int i = 1; i < players->size(); i++) {
        if (scores[i] > max) {
            max = scores[i];
        }
<<<<<<< HEAD
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
=======
        
        //check if there is a tie
        int count = 0;
        vector<Player*>* tiedPlayers = new vector<Player*>(players->size());
        vector<bool>* tied = new vector<bool>(players->size());
        for (int i = 0; i < players->size(); i++) {
            
            if (max == scores[i]) {
                
                count++;
                tiedPlayers->at(i) = players->at(i);
                tied->at(i) = true;
            }
        }
        
        //if there is a tie enter this
        if (count >= 2) {
            vector<int>* winner = new vector<int>();
            winner = fewestEmptySpaces(tiedPlayers, tied);

            //displays the winner/winners (in case of a shared win)
            if (winner->size() == 1) {
                cout << "\nThe winner is: ";
                cout << players->at(winner->at(0))->getID() << endl;
                cout << "With " << max << " points!" << endl;
            }
            else {
                cout << "\nThe winners are: ";
                cout << players->at(winner->at(0))->getID();
                for (int i = 1; i < winner->size(); i++) {
                    cout <<", " << players->at(winner->at(i))->getID();
                }
                cout << "\nWith " << max << " points!" << endl;
            }
            
>>>>>>> 8e91389511ebc22164b15d66c84474c0ea90bbfc
        }
    }

    //no tie; displays the winner, and their points
    else {

        cout << "\nThe winner is: ";
        for (int i = 0; i < players->size(); i++) {
            if (max == players->at(i)->getVillageBoard()->countPoints()) {
                cout << players->at(i)->getID() << endl;
            }
        }
        cout << "With " << max << " points!" << endl;
    }


}

//returns the index of the player between the ones indicated
vector<int>* fewestEmptySpaces(vector<Player*>* players, vector<bool>* tied) {
    
    vector<int>* emptySpaces = new vector<int>(players->size());
    for (int i = 0; i < players->size(); i++) {
        emptySpaces->at(i) = players->at(i)->getVillageBoard()->numberOfEmptySpaces();
        
    }
    
    int maxScore = emptySpaces->at(0);
    
    bool twoMaxScores = false;
    for (int i = 0; i < players->size(); i++) {
        
        if (tied->at(i)) {
            
            if (emptySpaces->at(i) < maxScore) {
                maxScore = emptySpaces->at(i);
                twoMaxScores = false;
            }
            else if (emptySpaces->at(i) == maxScore && i!=0) {
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
                vector<int>* indexesWinners = new vector<int>();
                indexesWinners->push_back(indexWinner);
                
                return indexesWinners;
            } 
            indexWinner++;
        }
    }
}

vector<int>* leastBuildingsLeftOver(vector<Player*>* players, vector<bool>* tied) {
    
    vector<int>* buildingsLeftover = new vector<int>(players->size());
    for (int i = 0; i < players->size(); i++) {
        buildingsLeftover->at(i) = players->at(i)->getBuildings()->size(); //I assume that we don't count the numbers... do we?
    }
    

    int maxScore = buildingsLeftover->at(0);
    bool twoMaxScores = false;
    for (int i = 0; i < players->size(); i++) {
        if (tied->at(i)) {
            if (buildingsLeftover->at(i) < maxScore) {
                maxScore = buildingsLeftover->at(i);
                twoMaxScores = false;
            }
            else if (buildingsLeftover->at(i) == maxScore && i!=0) {
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
            i++;
        }
    }
}

/*int main() {

    vector<Player*>* playerVector1 = new vector<Player*>();
    vector<Player*>* playerVector2 = new vector<Player*>();
    vector<Player*>* playerVector3 = new vector<Player*>();
    vector<Player*>* playerVector4 = new vector<Player*>();

    Player* player1 = new Player();
    Player* player2 = new Player();
    Player* player3 = new Player();
    Player* player4 = new Player();
    Player* player5 = new Player();
    Player* player6 = new Player();
    Player* player7 = new Player();
    Player* player8 = new Player();

    //Case 1: Player 1 has more points than Player 2
    DeckBuilding* deckBuildings = new DeckBuilding();
    player1->getVillageBoard()->build(deckBuildings->draw(), 3, 1);
    player1->getVillageBoard()->build(deckBuildings->draw(), 3, 2);
    player1->getVillageBoard()->build(deckBuildings->draw(), 3, 3);
    player1->getVillageBoard()->build(deckBuildings->draw(), 3, 4);
    player1->getVillageBoard()->build(deckBuildings->draw(), 3, 0);


    player2->getVillageBoard()->build(deckBuildings->draw(), 2, 1);
    player2->getVillageBoard()->build(deckBuildings->draw(), 2, 2);
    player2->getVillageBoard()->build(deckBuildings->draw(), 2, 3);
    player2->getVillageBoard()->build(deckBuildings->draw(), 2, 4);
    player2->getVillageBoard()->build(deckBuildings->draw(), 2, 0);

    playerVector1->push_back(player1);
    playerVector1->push_back(player2);

    cout << "\nPlayer #" << player1->getID() << endl;
    player1->getVillageBoard()->displayVGmap();
    cout << "\nPlayer #" << player2->getID() << endl;
    player2->getVillageBoard()->displayVGmap();

    gameTie(playerVector1);


    //case 2: Both players have equal points, however player 3 wins since they have more buildings on their board.
<<<<<<< HEAD
    player3->getVillageBoard()->build(new Building(), 3, 1);
    player3->getVillageBoard()->build(new Building(), 3, 2);
    player3->getVillageBoard()->build(new Building(), 3, 3);
    player3->getVillageBoard()->build(new Building(), 3, 4);
    player3->getVillageBoard()->build(new Building(), 3, 0);
    player3->getVillageBoard()->build(new Building(), 2, 2);

    player4->getVillageBoard()->build(new Building(), 3, 1);
    player4->getVillageBoard()->build(new Building(), 3, 2);
    player4->getVillageBoard()->build(new Building(), 3, 3);
    player4->getVillageBoard()->build(new Building(), 3, 4);
    player4->getVillageBoard()->build(new Building(), 3, 0);
=======
    player3->getVillageBoard()->build(deckBuildings->draw(), 3, 1);
    player3->getVillageBoard()->build(deckBuildings->draw(), 3, 2);
    player3->getVillageBoard()->build(deckBuildings->draw(), 3, 3);
    player3->getVillageBoard()->build(deckBuildings->draw(), 3, 4);
    player3->getVillageBoard()->build(deckBuildings->draw(), 3, 0);
    player3->getVillageBoard()->build(deckBuildings->draw(), 2, 2);
>>>>>>> 8e91389511ebc22164b15d66c84474c0ea90bbfc

    player4->getVillageBoard()->build(deckBuildings->draw(), 3, 1);
    player4->getVillageBoard()->build(deckBuildings->draw(), 3, 2);
    player4->getVillageBoard()->build(deckBuildings->draw(), 3, 3);
    player4->getVillageBoard()->build(deckBuildings->draw(), 3, 4);
    player4->getVillageBoard()->build(deckBuildings->draw(), 3, 0);

    
    playerVector2->push_back(player3);
    playerVector2->push_back(player4);

    cout << "\nPlayer #" << player3->getID() << endl;
    player3->getVillageBoard()->displayVGmap();
    cout << "\nPlayer #" << player4->getID() << endl;
    player4->getVillageBoard()->displayVGmap();

    gameTie(playerVector2);
<<<<<<< HEAD

=======
    
>>>>>>> 8e91389511ebc22164b15d66c84474c0ea90bbfc
    //case 3: Both players have equal points, however player 6 wins since they have more buildings in their hand.
    player5->getVillageBoard()->build(deckBuildings->draw(), 3, 1);
    player5->getVillageBoard()->build(deckBuildings->draw(), 3, 2);
    player5->getVillageBoard()->build(deckBuildings->draw(), 3, 3);
    player5->getVillageBoard()->build(deckBuildings->draw(), 3, 4);
    player5->getVillageBoard()->build(deckBuildings->draw(), 3, 0);

    player6->getVillageBoard()->build(deckBuildings->draw(), 3, 1);
    player6->getVillageBoard()->build(deckBuildings->draw(), 3, 2);
    player6->getVillageBoard()->build(deckBuildings->draw(), 3, 3);
    player6->getVillageBoard()->build(deckBuildings->draw(), 3, 4);
    player6->getVillageBoard()->build(deckBuildings->draw(), 3, 0);

    //Player5 will have 2 buildings leftover 
    player5->drawBuilding(*(deckBuildings));
    player5->drawBuilding(*(deckBuildings));

    //Player6 will have 1 building leftover 
    player6->drawBuilding(*(deckBuildings));

    playerVector3->push_back(player5);
    playerVector3->push_back(player6);

    cout << "\nPlayer #" << player5->getID() << endl;
    player5->getVillageBoard()->displayVGmap();
    cout << "\nPlayer #" << player6->getID() << endl;
    player6->getVillageBoard()->displayVGmap();

    gameTie(playerVector3);

    //case 4: Both players have equal points, board spaces and buildings leftover
    player7->getVillageBoard()->build(deckBuildings->draw(), 3, 1);
    player7->getVillageBoard()->build(deckBuildings->draw(), 3, 2);
    player7->getVillageBoard()->build(deckBuildings->draw(), 3, 3);
    player7->getVillageBoard()->build(deckBuildings->draw(), 3, 4);
    player7->getVillageBoard()->build(deckBuildings->draw(), 3, 0);

    player8->getVillageBoard()->build(deckBuildings->draw(), 3, 1);
    player8->getVillageBoard()->build(deckBuildings->draw(), 3, 2);
    player8->getVillageBoard()->build(deckBuildings->draw(), 3, 3);
    player8->getVillageBoard()->build(deckBuildings->draw(), 3, 4);
    player8->getVillageBoard()->build(deckBuildings->draw(), 3, 0);

<<<<<<< HEAD
    //Player5 will have 2 buildings leftover 
    player7->drawBuilding(*(deckBuildings));
    player7->drawBuilding(*(deckBuildings));

    //Player6 will have 2 building leftover 
=======
    //Player7 will have 2 buildings leftover 
    player7->drawBuilding(*(deckBuildings));
    player7->drawBuilding(*(deckBuildings));

    //Player8 will have 2 building leftover 
>>>>>>> 8e91389511ebc22164b15d66c84474c0ea90bbfc
    player8->drawBuilding(*(deckBuildings));
    player8->drawBuilding(*(deckBuildings));

    playerVector4->push_back(player7);
    playerVector4->push_back(player8);

    cout << "\nPlayer #" << player7->getID() << endl;
    player7->getVillageBoard()->displayVGmap();
    cout << "\nPlayer #" << player8->getID() << endl;
    player8->getVillageBoard()->displayVGmap();

    gameTie(playerVector4);

<<<<<<< HEAD
    //Fix Memory Leaks
=======
>>>>>>> 8e91389511ebc22164b15d66c84474c0ea90bbfc
    delete player1;
    delete player2;
    delete player3;
    delete player4;
    delete player5;
    delete player6;
    delete player7;
    delete player8;

    delete playerVector1;
    delete playerVector2;
    delete playerVector3;
    delete playerVector4;

    delete deckBuildings;

<<<<<<< HEAD

    return 0;
}
=======
    return 0;
}*/
>>>>>>> 8e91389511ebc22164b15d66c84474c0ea90bbfc
