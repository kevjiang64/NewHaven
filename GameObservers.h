#pragma once

#include "Player.h";
#include <list>;

using namespace std;

//Default Model for specific Observers
class GameObserver
{
public:
	~GameObserver();
	virtual void update() = 0;
protected:
	GameObserver();
};

//Observer for part #1 (i)
class placeTileObserver : GameObserver
{
public:
	placeTileObserver();
	placeTileObserver(Player* aPlayer);
	~placeTileObserver();
	//Overrride GameObserver's update
	void update();
};

//Observer for part #1 (i)
class placeTileObserver : GameObserver
{
public:
	placeTileObserver();
	placeTileObserver(Player* aPlayer);
	~placeTileObserver();
	void display();
	//Overrride GameObserver's update
	void update();

private:
	Player* _subject;
};

//Observer for part #1 (ii)
class countBuildingObserver : GameObserver
{
public:
	countBuildingObserver();
	countBuildingObserver(Player* aPlayer);
	~countBuildingObserver();
	void display();
	//Overrride GameObserver's update
	void update();
private:
	Player* _subject;
};

//Observer for part #1 (iii)
class decreaseResourcesObserver : GameObserver
{
public:
	decreaseResourcesObserver();
	decreaseResourcesObserver(Player* aPlayer);
	~decreaseResourcesObserver();
	void display();
	//Overrride GameObserver's update
	void update();
private:
	Player* _subject;
};

//Default model for Subject
class Subject
{
public:
	virtual void attach(GameObserver* o);
	virtual void detach(GameObserver* o);
	virtual void notify();
	Subject();
	~Subject();
private:
	list<GameObserver*>* _observers;
};

