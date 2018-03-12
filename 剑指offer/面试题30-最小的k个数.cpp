#include <iostream>
#include <vector>
#include <functional>
#include <set>
#include <cstdlib>
#include <iterator>

using namespace::std;

void swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}

int Partition(int *arr, int length, int start, int end)
{
	if (nullptr == arr || length < 0
		|| start < 0 || end >= length)
		return 0;

	int index = start + rand() % (end - start + 1);
	swap(arr[index], arr[end]);

	int small = start - 1;

	for (index = start; index < end; ++index) {
		if (arr[index] < arr[end]) {
			++small;
			if (arr[small] != arr[index])
				swap(arr[small], arr[index]);
		}
	}

	++small;
	swap(arr[small], arr[end]);
	return small;
}

void getLeastNumbers(int *input, int n, int *output, int k)
{
	if (nullptr == input || nullptr == output ||
		n <= 0 || k > n || k <= 0)
		return;

	int start = 0, end = n - 1;
	int index = Partition(input, n, start, end);
	while (index != k - 1) {
		if (index > k - 1) {
			end = index - 1;
			index = Partition(input, n, start, end);
		}
		else {
			start = index + 1;
			index = Partition(input, n, start, end);
		}
	}

	for (int i = 0; i < k; ++i)
		output[i] = input[i];
}

void getLeastNumbers2(
	const vector<int> &data,
	multiset<int> &leastNumbers,
	int k)
{
	leastNumbers.clear();

	if (k < 1 || data.size() < k)
		return;

	for (vector<int>::const_iterator iter = data.begin();
		iter != data.end(); ++iter) {
		if (leastNumbers.size() < k)
			leastNumbers.insert(*iter);
		else {
			multiset<int>::const_iterator iterGreatest = leastNumbers.end();
			if (*iter < *prev(iterGreatest)) {
				leastNumbers.erase(iterGreatest);
				leastNumbers.insert(*iter);
			}
		}
	}

}

int main()
{
	int arr[] = { 2, 2, 3, -9, 5, 2, 4, 2, 1 };
	int length = sizeof(arr) / sizeof(arr[0]);
	int k = 7;
	int *output = new int[k];
	getLeastNumbers(arr, length, output, k);
	for (int i = 0; i < k; ++i)
		cout << output[i] << ' ';
	cout << endl;
	delete[] output;

	vector<int> vec(begin(arr), end(arr));
	multiset<int> leastNumbers;
	getLeastNumbers2(vec, leastNumbers, k);
	for (multiset<int>::const_iterator iter = leastNumbers.begin();
		iter != leastNumbers.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;

	return 0;
}