/*
https://www.cnblogs.com/hapjin/p/5597658.html
*/

#include <iostream>
#include <vector>

int max(int a, int b)
{
	return a > b ? a : b;
}

using namespace::std;

int LIS(int arr[], int length)
{
	int *lis = new int[length];
	for (int i = 0; i < length; ++i)
		lis[i] = 1;

	for (int i = 1; i < length; ++i) {
		for (int j = 0; j < i; ++j) {
			if (arr[i] > arr[j])
				lis[i] = max(lis[j] + 1, lis[i]);
		}
	}
	int max = lis[0];
	for (int i = 1; i < length; ++i)
		if (max < lis[i])
			max = lis[i];
	delete[] lis;
	return max;
}

int LIS(int arr[], int length, int result[])
{
	int *lis = new int[length];
	int **lisArr = new int*[length];
	for (int i = 0; i < length; ++i)
		lisArr[i] = new int[length];

	for (int i = 0; i < length; ++i) {
		lis[i] = 1;
		lisArr[i][0] = arr[i];
	}

	for (int i = 1; i < length; ++i) {
		for (int j = 0; j < i; ++j) {
			if (arr[i] > arr[j]
				&& lis[j] + 1 > lis[i]) {
				lis[i] = lis[j] + 1;
				for (int k = 0; k <= lis[j]; ++k){
					lisArr[i][k] = lisArr[j][k];
				}
				lisArr[i][lis[i] - 1] = arr[i];
			}
		}
	}
	int max = lis[0];
	int index;
	for (int i = 1; i < length; ++i)
		if (max < lis[i]) {
			max = lis[i];
			index = i;
		}
	for (int i = 0; i < lis[index]; ++i)
		result[i] = lisArr[index][i];
	delete[] lis;
	for (int i = 0; i < length; ++i)
		delete[] lisArr[i];
	delete[] lisArr;

	return max;
}

int main()
{
	int arr[] = { 5, 2, 8, 6, 3, 6, 9, 7 };
	int length = sizeof(arr) / sizeof(arr[0]);
	int *result = new int[length];
	int lisNum = LIS(arr, length);
	cout << lisNum << endl << endl;

	lisNum = LIS(arr, length, result);
	cout << lisNum << endl;
	for (int i = 0; i < lisNum; ++i)
		cout << result[i] << endl;
}