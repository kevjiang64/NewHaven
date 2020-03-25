//
//  VGMapLoader.cpp
//  COMP345_A1
//
//  Created by Justin Teixeira on 2020-02-21.
//  Copyright © 2020 Justin Teixeira. All rights reserved.
//

#include <stdio.h>
#include "VGMapLoader.h"
#include <sstream>
#include <algorithm>
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

VGMapLoader::VGMapLoader(int row, int col)
{
	testMap = new VGMap(row, col, "Milford");
}

bool fexists(ifstream& input, string fileName)
{
	return input.is_open();
}

int checkValidRow(ifstream& input)
{
	string str;
	while (input >> str) {
		if (str.compare("6") == 0)
		{
			cout << "The inputed value for the row is valid!\n";
			return 6;
		}
	}
	cout << "The inputed value for the row is invalid!\n";
	return 0;
}
int checkValidColumn(ifstream& input)
{
	string str;
	while (input >> str) {
		if (str.compare("5") == 0)
		{
			cout << "The inputed value for the column is valid!\n";
			return 5;
		}
	}
	cout << "The inputed value for the column is invalid!\n";
	return 0;
}
string checkValidName(ifstream& input, string name)
{
	string str;
	while (input >> str) {
		if (str.compare(name) == 0)
		{
			cout << "The inputed value for the board name is valid!\n";
			return str;
		}
	}
	cout << "The inputed value for the board name is invalid!\n";
	return "wrong";
}



