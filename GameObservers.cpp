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
}



