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

using namespace::std;

int getFirstDisconti(int arr[], int n)
{
	int maxNum, minNum;
	maxNum = minNum = arr[0];
	for (int i = 1; i < n; ++i) {
		if (arr[i] > maxNum)
			maxNum = arr[i];
		if (arr[i] < minNum)
			minNum = arr[i];
	}
	int len = maxNum - minNum;
	bool *newArr = new bool[len + 1];
	for (int i = 0; i < len + 1; ++i)
		newArr[i] = false;
	for (int i = 0; i < n; ++i) {
		int temp = arr[i];
		newArr[temp - minNum] = true;
	}
	int result;
	for (int i = 0; i < len + 1; ++i) {
		if (newArr[i] == false) {
			result = i + minNum;
			break;
		}
	}

	delete[] newArr; newArr = nullptr;
	return result;
}

void test1()
{
	//freopen("input.txt", "r", stdin);
	int arr[] = { 7, 6, 3, 2, 4, 0, -1, -2 };
	int n = sizeof(arr) / sizeof(arr[0]);
	cout << getFirstDisconti(arr, n) << endl;
}


int main(int argc, char* argv[])
{
	test1();

	return 0;
}