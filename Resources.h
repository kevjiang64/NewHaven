#pragma once

#include <iostream>
#include <vector>
using namespace std;

enum ResourceType {Wheat, Sheep, Timber, Stone};
enum ColorType {Green, Gray, Red, Yellow};
enum LabelType {Meadow, Quarry, Forest, Wheatfield};

class HarvestTile {
	private:
		int* topLeft;
		int* resources;

	public:
		HarvestTile();
		~HarvestTile();
		void display();
		void completeDisplay();
		void setResources(int r, int i) { resources[i] = r;  };
		void setTopLeft(int tl) { *topLeft = tl;  };
		int* getResources() { return resources; };
		int* getTopLeft() { return topLeft; };
};

class DeckHarvestTile {
	private:
        int* count;
        HarvestTile* allTiles;

	public:
		DeckHarvestTile();
		~DeckHarvestTile();
		void setCount(int c) { count = &c; };
		int* getCount() { return count; };
        HarvestTile* getAllHarvestTiles() { return allTiles; };
        HarvestTile draw();

};

class Building {
	private:
		int* label;
		int* number;
		bool* flipped;
        bool* used;

	public:
		Building();
		~Building();
		void display();
		void completeDisplay();
		void setLabel(int l) { *label = l; };
		void setNumber(int n) { *number = n; };
		void setFlipped(bool f) { *flipped = f; };
        void setUsed(bool u) { *used = u; };
        bool getUsed() { return *used; };
		int getLabel() { return *label; };
        int getNumber() { return *number; }
		bool isFlipped() { return *flipped; };
		
};

class DeckBuilding {
	private:
		int* totalCount;
        int** count;
        Building** allBuildings;

	public:
		DeckBuilding();
		~DeckBuilding();
        Building** getAllBuildings() { return allBuildings; };
		bool validBuilding(Building b);
		Building* draw();
};

class Hand {
	private:
		vector<int>* resourceMarkers;

	public:
		Hand();
		~Hand();
		void exchange(vector<int> resources);
		void printResources();
		vector<int>* getResourceMarkers() { return resourceMarkers; };
		void setResourceMarkers(vector<int> resources) { *resourceMarkers = resources; };
		void resetResourceMarkers();
};
