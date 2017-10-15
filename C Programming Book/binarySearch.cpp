#include <iostream>
#include <vector>

using namespace::std;

bool binarySearch(vector<int> &vec, int key);

int main()
{
	vector<int> vec = { 1, 2, 3, 4 };
	int key = 5;
	bool result = binarySearch(vec, key);
	if (result)
		cout << "find the element.\n";
	else
		cout << "don't find the element.\n";
}

bool binarySearch(vector<int> &vec, int key)
{
	vector<int>::iterator beg = vec.begin(), end = vec.end();
	vector<int>::iterator mid = vec.begin() + (end - beg) / 2;
	while (mid != end) {
		if (*mid == key)
			return true;
		else if (key < *mid)
			end = mid;
		else
			beg = mid + 1;
		mid = beg + (end - beg) / 2;
	}

	if (mid == end)
		return false;
}