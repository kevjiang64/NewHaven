//
//  VGMapLoader.h
//  COMP345_A1
//
//  Created by Justin Teixeira on 2020-02-21.
//  Copyright © 2020 Justin Teixeira. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <string>
#include "VGMap.h"

#ifndef VGMapLoader_h
#define VGMapLoader_h

class VGMapLoader {
public:
    VGMapLoader(int row, int col);
    VGMap getTestMap() { return *testMap; };
private:
    VGMap* testMap;
};

bool fexists(std::string input);
int checkValidRow(ifstream& input);
int checkValidColumn(ifstream& input);
string checkValidName(ifstream& input, string fileName);
#endif /* VGMapLoader_h */
