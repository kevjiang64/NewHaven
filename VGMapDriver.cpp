#include <string>
#include "VGMap.h"

using namespace std;

int main()
{
	//Creating valid/invalid cases of VGMaps
	//First
	string answer = "yes";

	while (answer == "yes")
	{
	cout << "hello";

		int row;
		int col;
		cout << "What will be the value of the row?";
		cin >> row;
		cout << "What will be the value of the col?";
		cin >> col;
		VGMap a = VGMap(row, col);

		if (row == 6 && col == 5)
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; i++)
				{
					a.getBoard()[i][j].fillAdjNodes(a.getBoard());
				}
			}
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; i++)
				{
					//Return number of adjNodes
					cout << (a.getBoard())[i][j].getSize((a.getBoard())[i][j].getAdjNode());
				}
			}
		}
		cout << "Do you want to test again?";
		cin >> answer;
	}
	return 0;
};