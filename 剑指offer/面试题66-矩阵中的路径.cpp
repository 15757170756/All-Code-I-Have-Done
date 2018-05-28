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

bool hasPathCore(char *matrix, int rows, int cols,
	int row, int col, char *str, int &pathLength, bool *visited)
{
	if (str[pathLength] == '\0')
		return true;
	bool hasPath = false;
	if (row >= 0 && col >= 0 && row < rows && col < cols
		&& matrix[row*cols + col] == str[pathLength]
		&& !visited[row*cols + col]) {
		++pathLength;
		visited[row*cols + col] = true;

		hasPath = hasPathCore(matrix, rows, cols, row, col - 1, str, pathLength, visited)
			|| hasPathCore(matrix, rows, cols, row - 1, col, str, pathLength, visited)
			|| hasPathCore(matrix, rows, cols, row, col + 1, str, pathLength, visited)
			|| hasPathCore(matrix, rows, cols, row + 1, col, str, pathLength, visited);

		if (!hasPath) {
			--pathLength;
			visited[row*cols + col] = false;
		}
	}

	return hasPath;
}

bool hasPath(char *matrix, int rows, int cols, char *str)
{
	if (matrix == nullptr || rows < 1 || cols < 1 || str == nullptr)
		return false;
	bool *visited = new bool[rows * cols];
	memset(visited, 0, rows*cols*sizeof(bool));
	int pathLength = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (hasPathCore(matrix, rows, cols, i, j, str, pathLength, visited))
				return true;
		}
	}

	delete[] visited;
	return false;
}

void test1()
{
	char *matrix = "abcesfcsadee";
	char *str1 = "bcced";
	char *str2 = "abcd";
	int rows = 3, cols = 4;
	cout << hasPath(matrix, rows, cols, str1) << endl;
	cout << hasPath(matrix, rows, cols, str2) << endl;
}


int main(int argc, char* argv[])
{
	test1();
	return 0;
}
