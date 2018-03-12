/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定包含N个整数的数组A1, A2, ... AN，你可以选择任意一个Ai，将Ai旋转到数组第一项，即将数组变成：

Ai, Ai+1, Ai+2, ... AN, A1, A2, ..., Ai-1

现在小Hi希望旋转之后的数组满足：

对于任意K(1 ≤ i ≤ N)，前K项的和都是正数。

例如对于A=[3, -5, 2, -2, 3, 0]，旋转成[3, 0, 3, -5, 2, -2]满足条件。

请你输出i，代表将Ai旋转到第一项满足条件。

如果有多解，你可以输出任意一个i。如果无解输出-1。

输入
第一行包含一个整数N。

第二行包含N个整数A1, A2, ... AN。

对于50%的数据，1 ≤ N ≤ 1000

对于100%的数据，1 ≤ N ≤ 100000, -1000000 ≤ Ai ≤ 1000000

输出
一个整数表示答案。

样例输入
6
3 -5 2 -2 3 0
样例输出
5
*/



#include <vector>
#include <iostream>
#include <algorithm>

using namespace::std;

void swap(vector<int> &vec, int x, int y)
{
	vec[x] ^= vec[y];
	vec[y] ^= vec[x];
	vec[x] ^= vec[y];
}

void reverse(vector<int> &vec, int x, int y)
{
	while (x < y)
		swap(vec, x++, y--);
}

void convert(vector<int> &vec, int index, int length)
{
	reverse(vec, 0, index - 2);
	reverse(vec, index - 1, length - 1);
	reverse(vec, 0, length - 1);
}

int rotateArray(vector<int> &vec, int length)
{
	for (int i = 1; i <= length; ++i) {
		vector<int> temp = vec;
		convert(temp, i, length);
		int sum = 0, cnt = 0;
		for (int j = 0; j < length; ++j) {
			sum += temp[j];
			if (sum > 0)
				++cnt;
			else
				break;
		}
		if (cnt == length)
			return i;
	}
	return -1;
}

int rotateArray2(vector<int> &vec, int length)
{
	for (int i = 0; i < length; ++i) {
		long long sum = 0, cnt = 0;
		for (int j = i, m = 0, k; m < length; ++m) {
			if (j < length) {
				k = j;
				++j;
			}
			else
				k = m + i - j;
			sum += vec[k];
			if (sum > 0)
				++cnt;
			else
				break;
		}
		if (cnt == length)
			return i + 1;
	}

	return -1;
}

int main()
{
	int N;
	cin >> N;
	vector<int> vec(N);// = { 3, -5, 2, -2, 3, 0 };
	for (int &e : vec)
		cin >> e;
	int length = vec.size();
	//convert(vec, 5, 6);
	//for (int i = 0; i < vec.size(); ++i)
	//	cout << vec[i] << ' ';

	cout << rotateArray2(vec, length) << endl;
}

/*
结果:Accepted
得分:100 / 100
*/
