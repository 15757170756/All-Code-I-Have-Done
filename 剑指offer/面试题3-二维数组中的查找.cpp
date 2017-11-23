#include <iostream>

using namespace::std;

bool isFound(int(*matrix)[4], int rows, int cols, int number);

int main()
{
	int matrix[4][4] = { { 1, 2, 8, 9 },
	{ 2, 4, 9, 12 },
	{ 4, 7, 10, 13 },
	{ 6, 8, 11, 15 } };

	int number = 7;

	bool result = isFound(matrix, 4, 4, number);
	//bool result = isFound(nullptr, 4, 4, number);
	//bool result = isFound(matrix, 4, 4, 20);
	cout << boolalpha << result << noboolalpha << endl;

	return 0;
}

bool isFound(int(*matrix)[4], int rows, int cols, int number)
{
	bool found = false;
	if (matrix == nullptr) {
		printf("error!\n");
		return false;
	}

	if (matrix != nullptr && rows > 0 && cols > 0) {
		int row = 0;
		int column = cols - 1;
		while (row < rows && column >= 0) {
			if (matrix[row][column] == number) {
				found = true;
				break;
			}
			else if (matrix[row][column] > number)
				--column;
			else
				++row;
		}
	}

	return found;
}




