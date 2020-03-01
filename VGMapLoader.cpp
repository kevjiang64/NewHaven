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
	testMap = new VGMap(row, col);
}

bool fexists(string fileName)
{
	ifstream ifile(fileName);
	return ifile.good();
}

int checkValidRow(string file)
{
	ifstream ifile(file);
	string str;
	while (getline(ifile,str)) {
		if (str.find("Row:6") != std::string::npos)
		{
			cout << "The inputed value for the row is valid!\n";
			return 6;
		}
	}
	cout << "The inputed value for the row is invalid!\n";
	return 0;
}

int checkValidColumn(string file)
{
	ifstream ifile(file);
	string str;
	while (getline(ifile, str)) {
		if (str.find("Column:5") != std::string::npos)
		{
			cout << "The inputed value for the column is valid!\n";
			return 5;
		}
	}
	cout << "The inputed value for the column is invalid!\n";
	return 0;
}

