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
//		int* getResources() { return *resources; }; // not sure
		int* getTopLeft() { return topLeft; }; // not sure
//		static void createHarvestTile(HarvestTile newTile);
};

class DeckHarvestTile {
	private:
        int* count;

	public:
		DeckHarvestTile();
		~DeckHarvestTile();
		void setCount(int c) { count = &c; };
		int* getCount() { return count;  }; // not sure
        HarvestTile draw();

};

class Building {
	private:
		int* label;
//		int* color;
		int* number;
        int count[4][6];

	public:
		Building();
		~Building();
//		void setLabel(LabelType l) { label = &l; };
//		void setColor(ColorType c) { color = &c;  };
		void setNumber(int n) { number = &n; };
//        void setIntColot(int ic) { intColor = &ic; };
//		LabelType* getLabel() { return label; }; // not sure
//		ColorType* getColor() { return color; } // not sure
		int* getNumber() { return number; } // not sure
//        int* getIntColor() { return intColor; }; // not sure
//		static void createBuilding(Building newBuilding);
};

class DeckBuilding {
	private:
		int* totalCount;
        int* count;

	public:
		DeckBuilding();
		~DeckBuilding();
        void setCount(int c[]) { count = c; };
        int* getCount() { return count; };
		Building* draw(int num);
};

class Hand {
	private:
		int* resourcesCount;

	public:
		void exchange();

};
