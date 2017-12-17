#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace::std;

void printMatrixClockWisely(int** numbers, int rows, int columns)
{
	if (!numbers || rows <= 0 || columns <= 0)
		return;
	int start = 0;
	while (columns > start * 2 &&
		rows > start * 2) {

		int endX = columns - 1 - start;
		int endY = rows - 1 - start;

		//从左到右打印一行
		for (int i = start; i <= endX; ++i) {
			int number = numbers[start][i];
			cout << number << ' ';
		}

		//从上到下打印一列
		if (start < endY) {
			for (int i = start + 1; i <= endY; ++i) {
				int number = numbers[i][endX];
				cout << number << ' ';
			}
		}

		//从右到左打印一行
		if (start < endX && start < endY) {
			for (int i = endX - 1; i >= start; --i) {
				int number = numbers[endY][i];
				cout << number << ' ';
			}
		}

		//从下到上打印一列
		if (start < endX &&
			start < endY - 1) {
			for (int i = endY - 1; i >= start + 1; --i) {
				int number = numbers[i][start];
				cout << number << ' ';
			}
		}

		++start;
	}
}


//自己再写一遍的版本
void printMatrixClockWisely1(int** numbers, int rows, int columns)
{
	if (!numbers || rows <= 0 || columns <= 0)
		return;
	int start = 0;
	while (rows > start * 2 &&
		columns > start * 2) {
		int endX = columns - 1 - start;
		int endY = rows - 1 - start;

		for (int i = start; i <= endX; ++i)
			cout << numbers[start][i] << ' ';

		if (start < endY)
			for (int i = start + 1; i <= endY; ++i)
				cout << numbers[i][endX] << ' ';

		if (start < endX &&
			start < endY)
			for (int i = endX - 1; i >= start; --i)
				cout << numbers[endY][i] << ' ';

		//这里其实还得这么判断边界
		//因为从左下角往上一个开始打印
		if (start < endX &&
			start < endY - 1)
			for (int i = endY - 1; i >= start + 1; --i)
				cout << numbers[i][start] << ' ';

		++start;
	}
}

int main()
{
	int rows = 5, colnums = 1;
	int** numbers = new int*[rows];
	for (int i = 0; i < rows; ++i) {
		numbers[i] = new int[colnums];
		for (int j = 0; j < colnums; ++j)
			numbers[i][j] = i*colnums + j + 1;
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < colnums; ++j)
			cout << numbers[i][j] << ' ';
		cout << endl;
	}

	printMatrixClockWisely(numbers, rows, colnums);
	cout << endl;
	printMatrixClockWisely1(numbers, rows, colnums);

	for (int i = 0; i < rows; ++i)
		delete[](int*)numbers[i];

	delete[] numbers;
	return 0;
}

