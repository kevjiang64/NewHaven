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
	_subject->attach(this, true);
	
}

placeTileObserver::~placeTileObserver()
{
	_subject->detach(this, true);
}

void placeTileObserver::update()
{
	display();
}
void placeTileObserver::display()
{
	cout << "tile observer" << endl;
	_subject->getHand()->printResources();
}
countBuildingObserver::countBuildingObserver(Player* aPlayer)
{
	_subject = aPlayer;
	_subject->attach(this, false);
}

countBuildingObserver::~countBuildingObserver()
{
	_subject->detach(this, false);
}

void countBuildingObserver::update()
{
	display();
}

void countBuildingObserver::display()
{
	cout << "count building observer" << endl;
	cout << "The number of building on the board of player #" << _subject->getID() << " is: " << _subject->getVillageBoard()->getNbBuildings() << endl;
}

decreaseResourcesObserver::decreaseResourcesObserver(Player* aPlayer)
{
	_subject = aPlayer;
	_subject->attach(this, false);
}

decreaseResourcesObserver::~decreaseResourcesObserver()
{
	_subject->detach(this, false);
}

void decreaseResourcesObserver::update()
{
	display();
}

void decreaseResourcesObserver::display()
{
	cout << "decrease resources observer" << endl;
	_subject->getHand()->printResources();
}

statsObserver::statsObserver(vector<Player*>* vectorPlayer)
{
	_subject = vectorPlayer;
	for (int i = 0; i < vectorPlayer->size(); i++) {
		_subject->at(i)->attach(this, false);
	}
}

statsObserver::~statsObserver()
{
	for (int i = 0; i < _subject->size(); i++) {
		_subject->at(i)->detach(this, false);
	}
}

void statsObserver::update()
{
	display();
}

void statsObserver::display()
{
	cout << "statsObserver : " << endl;
	for (int i = 0; i < _subject->size(); i++) {
		Player* currentPlayer = _subject->at(i);
		cout << "Player #" << currentPlayer->getID() << endl;
		currentPlayer->getVillageBoard()->displayVGmap();
		currentPlayer->getVillageBoard()->countPoints();
		cout << "Number of colonists attracted: " << currentPlayer->getVillageBoard()->getPoints() << endl;
		currentPlayer->getHand()->printResources();
	}
}

winnerObserver::winnerObserver(vector<Player*>* vectorPlayer)
{
	_subject = vectorPlayer;
	for (int i = 0; i < vectorPlayer->size(); i++) {
		_subject->at(i)->attach(this, false);
	}
}

winnerObserver::~winnerObserver()
{
	for (int i = 0; i < _subject->size(); i++) {
		_subject->at(i)->detach(this, false);
	}
}

void winnerObserver::update()
{
	display();
}

void winnerObserver::display()
{
	cout << "winner observer : " << endl;
	vector<int>* indexWinners = new vector<int>();
	for (int i = 0; i < _subject->size(); i++) {
		if (_subject->at(i)->getWinner()) {
			indexWinners->push_back(i);
		}
	}
	if (indexWinners->size() == 0) cout << "Error, no winner!" << endl;
	else if (indexWinners->size() == 1) {
		cout << "\n\nThe winner is: Player #" << _subject->at(indexWinners->at(0))->getID();
	}
	else {
		cout << "\n\nIt is a tie!" << endl;
		cout << "\n\nThe winners are: Player #" << _subject->at(0)->getID();
		for (int i = 0; i < indexWinners->size(); i++) {
			if (i == indexWinners->size() - 1) {
				cout << " and Player #" << _subject->at(indexWinners->at(i))->getID();
			}
			else {
				cout << ", Player #" << _subject->at(indexWinners->at(i))->getID();
			}
			
		}
	}
	cout << " with " << _subject->at(indexWinners->at(0))->getVillageBoard()->getPoints() << " points!" << endl;
	cout << "\nCongratulations!!" << endl;
}

