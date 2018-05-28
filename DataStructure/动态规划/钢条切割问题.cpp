#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <ctime>
#include <cassert>
#include <algorithm>

using namespace::std;

// this is the most basic recursive version implementation
int cut_rot(int p[], int n)
{
	if (n == 0)
		return 0;

	int q = INT_MIN;
	for (int i = 0; i < n; ++i) {
		int res = p[i] + cut_rot(p, n - i - 1);
		q = max(q, res);
	}

	return q;
}

// memoized version of cut_rod
int memoized_cut_rod(int p[], int n)
{
	// create an array table to store memoized values
	int temp[100] = {};
	int q = -1;
	if (n == 0)
		return 0;

	if (temp[n] > 0)
		return temp[n];

	else {
		for (int i = 0; i < n; ++i) {
			int res = p[i] + cut_rot(p, n - i - 1);
			q = max(q, res);
		}
	}

	return q;
}

// cut_rod using bottom up approach
int bottom_cut_rod(int p[], int n)
{
	int r[100] = {};
	r[0] = 0;
	for (int j = 0; j < n; ++j) {
		int q = -5;
		for (int i = 0; i <= j; ++i) {
			q = max(q, p[i] + r[j - i]);
		}
		r[j + 1] = q;
	}

	return r[n];
}

int main()
{
	int arr[] = { 1, 5, 8, 9, 10, 17, 17,
		20, 24, 30, 31, 32, 33, 34, 35,
		36, 37, 38 };

	int n = 0;
	cout << cut_rot(arr, n) << endl;
	cout << memoized_cut_rod(arr, n) << endl;
	cout << bottom_cut_rod(arr, n) << endl;
	return 0;
}

