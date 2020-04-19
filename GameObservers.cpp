#include "GameObservers.h"
#include "Player.h"
#include <iostream>

using namespace std;

//Creating a list to attach observers
/*Subject::Subject()
{
	_observers = new list<GameObserver*>;
}
//Destructor
Subject::~Subject()
{
	delete _observers;
}
//Putting a specific observer into a subject's list of observers
void Subject::attach(GameObserver* o)
{
	_observers->push_back(o);
}
//Removing a specific observer from a subject's list of observers
void Subject::detach(GameObserver* o)
{
	_observers->remove(o);
}
//Updating every observer's information
void Subject::notify()
{
	for (list<GameObserver*>::iterator i = _observers->begin(); i != _observers->end(); i++)
	{
		(*i)->update();
	}
}*/

GameObserver::GameObserver() {
}

GameObserver::~GameObserver() {

}

placeTileObserver::placeTileObserver(Player* aPlayer)
{
	
	_subject = aPlayer;
	_subject->attach(this, 0);
	
}

placeTileObserver::~placeTileObserver()
{
	_subject->detach(this, 0);
}

void placeTileObserver::update()
{
	display();
}
void placeTileObserver::display()
{
	cout << "\n-----------------------------" << endl;
	cout << "Player #" << _subject->getID() << " has placed a tile on the board!" << endl;
	_subject->getHand()->printResources();
}
countBuildingObserver::countBuildingObserver(Player* aPlayer)
{
	_subject = aPlayer;
	_subject->attach(this, 1);
}

countBuildingObserver::~countBuildingObserver()
{
	_subject->detach(this, 1);
}

void countBuildingObserver::update()
{
	display();
}

void countBuildingObserver::display()
{
	cout << "\n-----------------------------" << endl;
	cout << "Player #" << _subject->getID() << " placed a building!" << endl;
	cout << "\nThe number of buildings on the board of player #" << _subject->getID() << " is: " << (_subject->getVillageBoard()->getNbBuildings()) << endl;
}

decreaseResourcesObserver::decreaseResourcesObserver(Player* aPlayer)
{
	_subject = aPlayer;
	_subject->attach(this, 1);
}

decreaseResourcesObserver::~decreaseResourcesObserver()
{
	_subject->detach(this, 1);
}

void decreaseResourcesObserver::update()
{
	display();
}

void decreaseResourcesObserver::display()
{
	_subject->getHand()->printResources();
}

statsObserver::statsObserver(vector<Player*>* vectorPlayer)
{
	_subject = vectorPlayer;
	for (int i = 0; i < vectorPlayer->size(); i++) {
		_subject->at(i)->attach(this, 1);
		_subject->at(i)->attach(this, 3);
	}
}

statsObserver::~statsObserver()
{
	for (int i = 0; i < _subject->size(); i++) {
		_subject->at(i)->detach(this, 1);
		_subject->at(i)->detach(this, 3);
	}
}

void statsObserver::update()
{
	display();
}

void statsObserver::display()
{
	cout << "\n-------Game statistics : -------" << endl;
	for (int i = 0; i < _subject->size(); i++) {
		Player* currentPlayer = _subject->at(i);
		cout << "\nPlayer #" << currentPlayer->getID() << endl;
		currentPlayer->getVillageBoard()->displayVGmap();
		currentPlayer->getVillageBoard()->countPoints();
		cout << "\nNumber of colonists attracted: " << currentPlayer->getVillageBoard()->getPoints() << endl;
		currentPlayer->getHand()->printResources();
	}
	cout << "----------------------------------" << endl;
}

winnerObserver::winnerObserver(vector<Player*>* vectorPlayer)
{
	_subject = vectorPlayer;
	for (int i = 0; i < vectorPlayer->size(); i++) {
		_subject->at(i)->attach(this, 2);
	}
}

winnerObserver::~winnerObserver()
{
	for (int i = 0; i < _subject->size(); i++) {
		_subject->at(i)->detach(this, 2);
	}
}

void winnerObserver::update()
{
	display();
}

void winnerObserver::display()
{
	
	vector<int>* indexWinners = new vector<int>();
	for (int i = 0; i < _subject->size(); i++) {
		if (_subject->at(i)->getWinner()) {
			indexWinners->push_back(i);
		}
	}
	if (indexWinners->size() == 0) cout << "Error, no winner!" << endl;
	else if (indexWinners->size() == 1) {
		cout << "\n\nThe winner is: Player #" << _subject->at(indexWinners->at(0))->getID();
		cout << " with " << _subject->at(indexWinners->at(0))->getVillageBoard()->getPoints() << " points!" << endl;
		cout << "\nCongratulations!!\n" << endl;
	}
	else {
		cout << "\n\nIt is a tie!" << endl;
		cout << "\nThe winners are: Player #" << _subject->at(0)->getID();
		for (int i = 1; i < indexWinners->size(); i++) {
			if (i == indexWinners->size() - 1) {
				cout << " and Player #" << _subject->at(indexWinners->at(i))->getID();
			}
			else {
				cout << ", Player #" << _subject->at(indexWinners->at(i))->getID();
			}
			
		}
		cout << " with " << _subject->at(indexWinners->at(0))->getVillageBoard()->getPoints() << " points!" << endl;
		cout << "\nCongratulations!!\n" << endl;
	}

	cout << "All scores: " << endl;
	for (int i = 0; i < _subject->size(); i++) {
		cout << "Player #" << _subject->at(i)->getID() << ": " << _subject->at(i)->getVillageBoard()->getPoints() << endl;
	}
	
	
}

