#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>
#include <unordered_set>
#include <sstream>
#include <map>
#include <iterator>
#include <set>
#include <stack>
#include <deque>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <numeric>

using namespace::std;

int getDigitSum(int number)
{
	int result = 0;
	while (number) {
		result += number % 10;
		number /= 10;
	}
	return result;
}

bool check(int threshold, int rows, int cols,
	int row, int col, bool *visited)
{
	if (row >= 0 && row < rows && col >= 0 && col < cols
		&& (getDigitSum(row) + getDigitSum(col)) <= threshold
		&& !visited[row*cols + col])
		return true;
	return false;
}

int movingCountCore(int threshold, int rows, int cols,
	int row, int col, bool *visited)
{
	int cnt = 0;
	if (check(threshold, rows, cols, row, col, visited)) {
		visited[row*cols + col] = true;
		cnt = 1 + movingCountCore(threshold, rows, cols, row, col - 1, visited)
			+ movingCountCore(threshold, rows, cols, row - 1, col, visited)
			+ movingCountCore(threshold, rows, cols, row, col + 1, visited)
			+ movingCountCore(threshold, rows, cols, row + 1, col, visited);
	}

	return cnt;
}

int movingCount(int threshold, int rows, int cols)
{
	bool *visited = new bool[rows*cols];
	memset(visited, 0, rows*cols*sizeof(bool));
	int count = movingCountCore(threshold, rows, cols, 0, 0, visited);
	delete[] visited;
	return count;
}

void test1()
{
	int threshold = 18;
	int rows = 20, cols = 21;
	cout << movingCount(threshold, rows, cols) << endl;
}


int main(int argc, char* argv[])
{
	test1();
	return 0;
}
