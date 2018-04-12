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
















//使用最长公共子序列求最长递增子序列
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <limits>
#include <climits>

using namespace::std;

int lcs(const vector<int> &vec1, const vector<int> &vec2, vector<vector<int>> &auxVec)
{
	int Length = vec1.size();
	if (Length < 1)
		return 0;
	vector<vector<int>> c(Length + 1, vector<int>(Length + 1));
	auxVec.assign(Length + 1, vector<int>(Length + 1));

	for (int i = 1; i <= Length; ++i) {
		for (int j = 1; j <= Length; ++j) {
			if (vec1[i - 1] == vec2[j - 1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				auxVec[i][j] = 0;
			}
			else if (c[i - 1][j] > c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
				auxVec[i][j] = 1;
			}
			else {
				c[i][j] = c[i][j - 1];
				auxVec[i][j] = 2;
			}
		}
	}

	for (int i = 0; i < Length + 1; ++i) {
		for (int j = 0; j < Length + 1; ++j)
			cout << c[i][j] << ' ';
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < Length + 1; ++i) {
		for (int j = 0; j < Length + 1; ++j)
			cout << auxVec[i][j] << ' ';
		cout << endl;
	}
	cout << endl;

	return c[Length][Length];
}

void printLCS(vector<vector<int>> &auxVec, const vector<int> &vec1,
	int i, int j)
{
	if (i == 0 || j == 0)
		return;
	if (auxVec[i][j] == 0) {
		printLCS(auxVec, vec1, i - 1, j - 1);
		cout << vec1[i - 1];
	}
	else if (auxVec[i][j] == 1)
		printLCS(auxVec, vec1, i - 1, j);
	else
		printLCS(auxVec, vec1, i, j - 1);
}

int main()
{
	vector<int> vec1 = { 3, 2, 1, 5, 9, 7, 8 };
	vector<int> vec2 = vec1;
	sort(vec2.begin(), vec2.end());
	vector<vector<int>> auxVec;
	cout << lcs(vec1, vec2, auxVec) << endl;
	printLCS(auxVec, vec1, vec1.size(), vec1.size());
	cout << endl;
	return 0;
}











//保存其中一个最长子序列
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <limits>
#include <climits>

using namespace::std;

int LIS(vector<int> &vec)
{
	int len = vec.size();
	vector<int> auxVec(len, 1);

	for (int i = 1; i < len; ++i) {
		for (int j = 0; j < i; ++j) {
			if (vec[i] > vec[j]) {
				auxVec[i] = max(auxVec[j] + 1, auxVec[i]);
			}
		}
	}
	int maxNum = auxVec[0];
	for (int i = 1; i < len; ++i) {
		if (maxNum < auxVec[i])
			maxNum = auxVec[i];
	}

	return maxNum;
}


int LIS(vector<int> &vec, vector<int> &result)
{
	int len = vec.size();
	vector<int> auxVec(len, 1);
	vector<vector<int>> lisArr(len, vector<int>(len));

	for (int i = 0; i < len; ++i)
		lisArr[i][0] = vec[i];

	for (int i = 1; i < len; ++i) {
		for (int j = 0; j < i; ++j) {
			if (vec[i] > vec[j]
				&& auxVec[j] + 1 > auxVec[i]) {
				auxVec[i] = auxVec[j] + 1;
				for (int k = 0; k <= auxVec[j]; ++k)
					lisArr[i][k] = lisArr[j][k];
				lisArr[i][auxVec[i] - 1] = vec[i];
			}
		}
	}
	int maxNum = auxVec[0];
	int maxIdx;
	for (int i = 1; i < len; ++i) {
		if (maxNum < auxVec[i]) {
			maxNum = auxVec[i];
			maxIdx = i;
		}
	}
	for (int i = 0; i < auxVec[maxIdx]; ++i)
		result.push_back(lisArr[maxIdx][i]);

	return maxNum;
}

int main()
{
	vector<int> vec = { 3, 2, 1, 5, 9, 7, 8 };
	cout << LIS(vec) << endl;
	vector<int> result;
	cout << LIS(vec, result) << endl;
	for (int e : result)
		cout << e << ' ';
	cout << endl;
	return 0;
}























//复杂度为o(nlgn)
/*
input:
7
3 2 1 5 4 7 8
output:
4
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <limits>
#include <climits>

using namespace::std;

int find(int *a, int len, int n)
{
	int left(0), right(len), mid = (left + right) / 2;
	while (left <= right)
	{
		if (n > a[mid]) left = mid + 1;
		else if (n < a[mid]) right = mid - 1;
		else return mid;
		mid = (left + right) / 2;
	}
	return left;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int n, a[100], c[100], i, j, len;
	cin >> n;

	for (int i = 0; i < n; i++)
		cin >> a[i];
	c[0] = -1;
	c[1] = a[0];
	len = 1;

	for (i = 1; i <= n; i++)
	{
		j = find(c, len, a[i]);
		c[j] = a[i];
		if (j > len)
			len = j;
	}

	cout << len << endl;
	return 0;
}