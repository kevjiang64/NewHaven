#pragma once

#include <iostream>
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
		void setResources(int r) { *resources = r;  };
		void setTopLeft(int tl) { topLeft = &tl;  };
		int* getResources() { return resources; };
		int* getTopLeft() { return topLeft; };
};

class DeckHarvestTile {
	private:
        int* count;

	public:
		DeckHarvestTile();
		~DeckHarvestTile();
		void setCount(int c) { count = &c; };
		int* getCount() { return count; };
        HarvestTile draw();

};

class Building {
	private:
		int* label;
		int* number;
		bool* flipped;
        int count[4][6];

	public:
		Building();
		~Building();
		void setLabel(int l) { *label = l; };
		void setNumber(int n) { *number = n; };
		void setFlipped(bool f) { *flipped = f; };
		int getLabel() { return *label; };
        int getNumber() { return *number; }
		bool isFlipped() { return *flipped; };
		
};

class DeckBuilding {
	private:
		int* totalCount;
        int** count;

	public:
		DeckBuilding();
		~DeckBuilding();
		bool validBuilding(Building b);
		Building draw();
};

class Hand {
	private:
		int* wheatCount;
		int* sheepCount;
		int* timberCount;
		int* stoneCount;

	public:
		Hand();
		~Hand();
		void exchange();
};
