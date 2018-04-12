#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <stack>

using namespace::std;

//wrong
bool isDuplicateWrong(int numbers[], int length, int *duplication)
{
	if (numbers == nullptr || length < 1)
		return false;
	for (int i = 0; i < length; ++i)
		if (numbers[i] < 0 || numbers[i] > length - 1)
			return false;

	for (int i = 0; i < length; ++i) {
		if (numbers[i] == i)
			continue;
		else if (numbers[i] == numbers[numbers[i]]) {
			*duplication = numbers[i];
			return true;
		}
		else if (numbers[i] != numbers[numbers[i]]) {
			swap(numbers[i], numbers[numbers[i]]);
		}
	}

	return false;
}

bool isDuplicate(int numbers[], int length, int *duplication)
{
	if (numbers == nullptr || length < 1)
		return false;
	for (int i = 0; i < length; ++i)
		if (numbers[i] < 0 || numbers[i] > length - 1)
			return false;

	for (int i = 0; i < length; ++i) {
		while (numbers[i] != i) {
			if (numbers[i] == numbers[numbers[i]]) {
				*duplication = numbers[i];
				return true;
			}
			swap(numbers[i], numbers[numbers[i]]);
		}
	}

	return false;
}

int main(int argc, char* argv[])
{
	const int n = 7;
	int arr[n] = { 3, 2, 0, 6, 6, 1, 4 };
	int du;
	cout << isDuplicateWrong(arr, n, &du) << endl;
	cout << du << endl;

	cout << isDuplicate(arr, n, &du) << endl;
	cout << du << endl;
}