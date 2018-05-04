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

vector<int> maxInWindows(const vector<int> &num, unsigned int size)
{
	vector<int> maxInWindows;
	if (num.size() >= size && size >= 1){
		deque<int> index;
		for (int i = 0; i < size; ++i) {
			while (!index.empty() && num[i] >= num[index.back()])
				index.pop_back();
			index.push_back(i);
		}

		for (int i = size; i < num.size(); ++i) {
			maxInWindows.push_back(num[index.front()]);
			while (!index.empty() && num[i] >= num[index.back()])
				index.pop_back();
			if (!index.empty() && index.front() <= (int)(i - size))
				index.pop_back();

			index.push_back(i);
		}
		maxInWindows.push_back(num[index.front()]);
	}
	return maxInWindows;
}

void test1()
{
	vector<int> vec = { 2, 3, 4, 2, 6, 2, 5, 2 };
	unsigned int size = 3;
	vector<int> result = maxInWindows(vec, size);
	for (int e : result)
		cout << e << ' ';
	cout << endl;
}


int main(int argc, char* argv[])
{
	test1();
	return 0;
}
