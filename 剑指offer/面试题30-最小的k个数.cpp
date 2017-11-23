/***************************************
使用C++ STL set等实现
****************************************/
#include <iostream>
#include <vector>
#include <set>
#include <functional>

using namespace::std;

using intSet = multiset<int, greater<int>>;
using setIterator = multiset<int, greater<int>>::iterator;

void getLeastNumbers(const vector<int>& data, intSet& leastNumbers, int k);

int main()
{
	vector<int> data = { 9, 8, 7, 6, 5, 4, 1, 2, 1 };
	int k = 3;
	intSet leastNum;
	getLeastNumbers(data, leastNum, k);

	for (auto e : leastNum)
		cout << e << ' ';
	cout << endl;

	return 0;
}

void getLeastNumbers(const vector<int>& data, intSet& leastNumbers, int k)
{
	leastNumbers.clear();

	if (k < 1 || data.size() < k)
		return;

	for (vector<int>::const_iterator iter = data.begin();
		iter != data.end(); ++iter) {
		if (leastNumbers.size() < k)
			leastNumbers.insert(*iter);

		else {
			setIterator iterGreatest = leastNumbers.begin();
			if (*iter < *iterGreatest) {
				leastNumbers.erase(iterGreatest);
				leastNumbers.insert(*iter);
			}
		}
	}
}

