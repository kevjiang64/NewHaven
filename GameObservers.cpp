#include "GameObservers.h";

//Creating a list to attach observers
Subject::Subject()
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
}

placeTileObserver::placeTileObserver(Player* aPlayer)
{
	_subject = aPlayer;
	//_subject.attach(aPlayer);
}

placeTileObserver::~placeTileObserver()
{
	//_subject.detach(aPlayer);
}

void placeTileObserver::update()
{
	display();
}
void placeTileObserver::display()
{

}
countBuildingObserver::countBuildingObserver(Player* aPlayer)
{
	_subject = aPlayer;
	//_subject.attach(aPlayer);
}

countBuildingObserver::~countBuildingObserver()
{
	//_subject.detach(aPlayer);
}

void countBuildingObserver::update()
{
	display();
}

void countBuildingObserver::display()
{

}

decreaseResourcesObserver::decreaseResourcesObserver(Player* aPlayer)
{
	_subject = aPlayer;
	//_subject.attach(aPlayer);
}

decreaseResourcesObserver::~decreaseResourcesObserver()
{
	//_subject.detach(aPlayer);
}

void decreaseResourcesObserver::update()
{
	display();
}

void decreaseResourcesObserver::display()
{

}



