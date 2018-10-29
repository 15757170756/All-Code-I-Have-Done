/*
N个点，围成一个圈，从某个点开始计数，
如果这个点为奇数，跳过一个数往下加，
如果为偶数，跳过两个数往下加，求最大值
输入：3
      2 3 2

输出 5
*/

#include <ctime>
#include <numeric>
#include <unordered_map>
#include <climits>
#include <cmath>
#include <cstdio>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

int fun(vector<int> &vec)
{
	int maxSum = -1;
	int curSum = 0;
	int n = vec.size();
	for (int i = 0; i < n; ++i) {
		curSum = 0;
		int k = i;
		bool flag = false;
		for (int j = i; j < n;) {
			if (flag == true && j >= k)
				break;
			curSum += vec[j];
			if (vec[j] % 2 == 1) {
				j += 2;
				if (flag == true && j >= k)
					break;
				if (j >= n) {
					j = j % n;
					flag = true;
				}
			}
			else {
				j += 3;
				if (flag == true && j >= k)
					break;
				if (j >= n) {
					j = j % n;
					flag = true;
				}
			}
		}
		maxSum = max(maxSum, curSum);
	}
	return maxSum;
}

int main(int argc, char *argv[]) 
{	
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;
	vector<int> vec(n);
	for (int i = 0; i < n; ++i)
		cin >> vec[i];
	cout << fun(vec) << endl;
	//cout << "wef" << endl;

	return 0;
}
