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




//自己写的，并给出切割方案
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <limits>
#include <climits>

using namespace::std;

int getMaxValue(vector<int> &vec, int n, vector<int> &plan)
{
	//int length = vec.size();
	vector<int> r(n + 1, 0);
	vector<vector<int>> allPlan;

	for (int j = 1; j <= n; ++j) {
		int p1, p2;
		int q = INT_MIN;
		for (int i = 1; i <= j; ++i) {
			int tempMax = vec[i] + r[j - i];
			if (tempMax > q) {
				q = tempMax;
				p1 = i, p2 = j - i;
			}
		}
		r[j] = q;
		vector<int> temp;
		temp.push_back(p1);
		for (int i = 0; i < allPlan.size(); ++i) {
			if (p2 == i + 1) {
				vector<int> vec = allPlan[i];
				for (int j = 0; j < vec.size(); ++j)
					temp.push_back(vec[j]);
			}
		}
		allPlan.push_back(temp);
	}
	plan = allPlan[n - 1];

	return r[n];
}

int main()
{
	vector<int> vec = { 0, 1, 5, 8, 9, 14, 17, 18, 20, 24, 30 };
	for (int n = 1; n <= 10; ++n) {
		vector<int> plan;
		cout << n << endl << getMaxValue(vec, n, plan) << endl;
		for (int e : plan)
			cout << e << ' ';
		cout << endl << endl;
	}

	return 0;
}