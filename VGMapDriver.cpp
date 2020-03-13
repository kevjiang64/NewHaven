#include <string>
#include "VGMap.h"

using namespace std;

int main()
{
	//Creating valid/invalid cases of VGMaps
	//First
	string answer = "yes";
	string board;

	while (answer == "yes")
	{
		int row;
		int col;
		cout << "What will be the value of the row?\n";
		cin >> row;
		cout << "What will be the value of the col?\n";
		cin >> col;
		cout << "What will be the name of the board?\n";
		cin >> board;
		VGMap a = VGMap(row, col, board);
		cout << "hello";

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
};