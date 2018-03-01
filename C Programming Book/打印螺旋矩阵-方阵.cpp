/*
这个只能打印方阵，
即rows=cols
*/

#include <iostream>

using namespace::std;

int main()
{
	while (1) {
		int rows, cols;
		cin >> rows >> cols;
		int** arr = new int*[rows];
		for (int i = 0; i < rows; ++i)
			arr[i] = new int[cols];
		int m = 1;
		for (int i = 0; i <= (rows - 1) / 2; ++i) {
			for (int j = i; j < cols - i; ++j)
				arr[i][j] = m++;
			for (int j = i + 1; j < rows - i; ++j)
				arr[j][cols - i - 1] = m++;
			for (int j = cols - 2 - i; j >= i; --j)
				arr[rows - 1 - i][j] = m++;
			for (int j = rows - 2 - i; j >= i + 1; --j)
				arr[j][i] = m++;
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				cout << arr[i][j] << ' ';
			}
			cout << endl;
		}
	}

	return 0;
}

