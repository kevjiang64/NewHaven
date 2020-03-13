#include <string>
#include "VGMap.h"

using namespace std;

/*int main()
{
	//Creating valid/invalid cases of VGMaps
	//First
	string answer = "yes";

	while (answer == "yes")
	{
		int row;
		int col;
		cout << "What will be the value of the row?\n";
		cin >> row;
		cout << "What will be the value of the col?\n";
		cin >> col;
		VGMap a = VGMap(row, col);

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				VGMap::Node node = a.getBoard()[i][j];
				
				cout << "Number of adjacent nodes at position (" << i << "," << j << ")" << " :" << node.getSize() << "\n";
			}
		}
		cout << "Do you want to test again?";
		cin >> answer;
	}
	return 0;
};*/