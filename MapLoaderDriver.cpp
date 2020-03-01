#include "VGMapLoader.h"
#include <iostream>
#include<conio.h>

int main()
{
	int row;
	int column;

	cout << "Test 1:\n";
	//Checking if a VGMap is valid or invalid
	if (fexists("valid.txt"))
	{
		row = checkValidRow("valid.txt");
		column = checkValidColumn("valid.txt");
		cout << "The Row Value is : " << row <<"\n";
		cout << "The Column Value is : " << column<<"\n";
		if (row == 6 && column == 5)
		{
			cout << "A VGMapLoader Object with a VGMap Object will be created\n\n";
			VGMapLoader a = VGMapLoader(row, column);
		}
	}

	cout << "Test 2\n";
	//Checking if a VGMap is valid or invalid
	if (fexists("invalid.txt"))
	{
		int row = checkValidRow("invalid.txt");
		int column = checkValidColumn("invalid.txt");
		if (row == 0 && column == 0)
		{
			cout << "A VGMapLoader Object will not be created\n";
		}
	}
	return 0;
}