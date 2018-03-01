#include <iostream>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>

using namespace::std;


void argSort(vector<int>& arrayIn, vector<int>& argcOut)
{
	multimap<int, int> intMap;
	for (int i = 0; i < arrayIn.size(); ++i)
		intMap.emplace(arrayIn[i], i);
	for (multimap<int, int>::const_iterator iter = intMap.begin();
		iter != intMap.end(); ++iter)
		argcOut.emplace_back(iter->second);
}

int findMinSortRegion(int arr[], int arrSize, int* m, int* n)
{
	*m = *n = -1;
	vector<int> vec;
	multimap<int, int> intMap;
	for (int i = 0; i < arrSize; ++i)
		intMap.emplace(arr[i], i);
	for (multimap<int, int>::const_iterator iter = intMap.begin();
		iter != intMap.end(); ++iter)
		vec.emplace_back(iter->second);

	for (int i = 0; i < vec.size(); ++i) {
		if (i != vec[i]) {
			*m = i;
			break;
		}
	}
	if (*m == -1)
		*m = 0;

	for (int i = vec.size() - 1; i >= 0; --i) {
		if (i != vec[i]) {
			*n = i;
			break;
		}
	}
	if (*n == -1)
		*n = 1;

	return 1;
}

int main(int argc, char* argv[])
{
	multimap<int, int> intMap;
	//int arr[] = { 1, 2, 4,7,1,2,3,4,5,6 };
	//int arr[] = { 20, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19 };
	//int arr[] = { 1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19 };
	int arr[] = { 1, 2, 3, 2, 2, 1, 1, 1, 1, 1 };
	int arrLen = sizeof(arr) / sizeof(arr[0]);
	cout << arrLen << endl;
	for (int i = 0; i < arrLen; ++i)
		intMap.emplace(arr[i], i);
	for (multimap<int, int>::const_iterator iter = intMap.begin();
		iter != intMap.end(); ++iter)
		cout << iter->first << ' ' << iter->second << endl;
	cout << endl << endl;
	int m, n;
	findMinSortRegion(arr, arrLen, &m, &n);
	cout << m << ' ' << n << endl;

	return 0;
}