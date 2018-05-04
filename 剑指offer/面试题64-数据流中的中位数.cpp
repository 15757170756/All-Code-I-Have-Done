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

template <typename T>
class DynamicArray
{
public:
	void insert(T num);
	T getMedian();
private:
	vector<T> min;
	vector<T> max;
};

template <typename T>
void DynamicArray<T>::insert(T num)
{
	if (((min.size() + max.size()) & 1) == 0) {
		if (max.size() > 0 && num < max[0]) {
			max.emplace_back(num);
			push_heap(max.begin(), max.end(), less<T>());

			num = max[0];
			pop_heap(max.begin(), max.end(), less<T>());
			max.pop_back();
		}
		min.emplace_back(num);
		push_heap(min.begin(), min.end(), greater<T>());
	}

	else {
		if (min.size() > 0 && num > min[0]) {
			min.emplace_back(num);
			push_heap(min.begin(), min.end(), greater<T>());

			num = min[0];
			pop_heap(min.begin(), min.end(), greater<T>());
			min.pop_back();
		}

		max.emplace_back(num);
		push_heap(max.begin(), max.end(), less<T>());
	}
}

template <typename T>
T DynamicArray<T>::getMedian()
{
	int size = min.size() + max.size();
	if (0 == size)
		throw exception("No numbers are available");

	T median = 0;
	if ((size & 1) == 1)
		median = min[0];
	else
		median = (min[0] + max[0]) / 2;

	return median;
}


void test1()
{
	//freopen("input.txt", "r", stdin);
	DynamicArray<int> arr;
	arr.insert(4);
	arr.insert(5);
	arr.insert(6);
	arr.insert(3);
	arr.insert(-1);
	arr.insert(-5);

	cout << arr.getMedian() << endl;
}


int main(int argc, char* argv[])
{
	test1();

	return 0;
}