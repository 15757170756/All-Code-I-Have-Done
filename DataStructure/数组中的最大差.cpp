
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
#include <unordered_map>

using namespace::std;

pair<int, int> getMaxValue1(vector<int> &vec)
{
	int len = vec.size();
	int maxNum = INT_MIN;
	int num1, num2;
	for (int i = 0; i < len - 1; ++i) {
		for (int j = i + 1; j < len; ++j) {
			int diff = vec[j] - vec[i];
			if (diff > maxNum) {
				maxNum = diff;
				num1 = vec[i];
				num2 = vec[j];
			}
		}
	}

	return make_pair(num1, num2);
}

pair<int, int> getMaxValue2(vector<int> &vec)
{
	int len = vec.size();
	int idx1 = 0, idx2 = 0;
	int minTemp = -1;
	int diff = 0;
	for (int i = 0; i < len; ++i) {
		if (minTemp != -1 && vec[i] - vec[minTemp] > diff) {
			diff = vec[i] - vec[minTemp];
			idx1 = minTemp;
			idx2 = i;
		}
		else if (vec[i] > vec[idx2]) {
			idx2 = i;
			diff = vec[idx2] - vec[idx1];
		}
		else if (vec[i] < vec[idx1]
			&& (minTemp == -1 || vec[i] < vec[minTemp]))
			minTemp = i;
	}

	return make_pair(vec[idx1], vec[idx2]);
}


void test1()
{
	vector<int> vec = { 3, 10, 11, 9, 1, 2, -1, 10, 7 };
	pair<int, int> p = getMaxValue1(vec);
	cout << p.first << ' ' << p.second << endl;

	p = getMaxValue2(vec);
	cout << p.first << ' ' << p.second << endl;
}

int main(int argc, char* argv[])
{
	test1();

}