#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace::std;

void adjustPlace1(int arr[], int arrLength)
{
	int oddNum = 0;
	for (int i = 0; i < arrLength; ++i)
		if (arr[i] % 2)
			++oddNum;

	for (int i = 0, j; i < oddNum;) {
		if (arr[i] % 2 == 0) {
			int temp = arr[i];
			for (j = i; j < arrLength - i; ++j) {
				arr[j] = arr[j + 1];
			}
			arr[j] = temp;
		}
		else
			++i;
	}
}

void swap(int& a, int& b)
{
	a = a + b;
	b = a - b;
	a = a - b;
}

void adjustPlace2(int arr[], int arrLength)
{
	if (arr == nullptr || arrLength == 0)
		return;

	int* pBegin = arr;
	int* pEnd = arr + arrLength - 1;
	while (pBegin < pEnd) {
		if ((*pBegin) % 2 == 0 &&
			(*pEnd) % 2 == 1)
			swap(*pBegin, *pEnd);
		else if ((*pBegin) % 2 == 1 &&
			(*pEnd) % 2 == 1)
			++pBegin;
		else if ((*pBegin) % 2 == 1 &&
			(*pEnd) % 2 == 0)
			--pEnd;
	}
}

/*
剑指offer的答案
*/
void adjustPlace3(int arr[], int arrLength)
{
	if (arr == nullptr || arrLength == 0)
		return;

	int* pBegin = arr;
	int* pEnd = arr + arrLength - 1;

	while (pBegin < pEnd) {
		while (pBegin < pEnd && (*pBegin & 0x1) != 0)
			++pBegin;

		while (pBegin < pEnd && (*pEnd & 0x1) == 0)
			--pEnd;

		if (pBegin < pEnd)
			swap(*pBegin, *pEnd);
	}
}

/*
扩展性解法：
适用函数指针用于判断
这个类似算法中的lambda函数
满足函数指针的放在前面，
不满足的放在后面
*/

void adjustPlace4Aux(int arr[], int arrLength, bool(*func)(int))
{
	if (arr == nullptr || arrLength == 0)
		return;

	int* pBegin = arr;
	int* pEnd = arr + arrLength - 1;

	while (pBegin < pEnd) {
		while (pBegin < pEnd && !func(*pBegin))
			++pBegin;

		while (pBegin < pEnd && func(*pEnd))
			--pEnd;

		if (pBegin < pEnd)
			swap(*pBegin, *pEnd);
	}
}

bool isEven(int n)
{
	return (n & 1) == 0;
}

void adjustPlace4(int arr[], int arrLength)
{
	adjustPlace4Aux(arr, arrLength, isEven);
}

/*
比如：将3的倍数放在前面，
不是3的倍数放在后面
*/
void adjustPlace5Aux(int arr[], int arrLength, bool(*func)(int))
{
	if (arr == nullptr || arrLength == 0)
		return;

	int* pBegin = arr;
	int* pEnd = arr + arrLength - 1;

	while (pBegin < pEnd) {
		while (pBegin < pEnd && !func(*pBegin))
			++pBegin;

		while (pBegin < pEnd && func(*pEnd))
			--pEnd;

		if (pBegin < pEnd)
			swap(*pBegin, *pEnd);
	}
}

bool isTimesOf3(int n)
{
	return n % 3 == 0;
}

void adjustPlace5(int arr[], int arrLength)
{
	adjustPlace5Aux(arr, arrLength, isTimesOf3);
}

int main()
{
	int arr[] = { 9, 12, 1, 2, 3, 4, 5, 6, 7, 2, 2, 4, 8, 1 };
	int arrLength = sizeof(arr) / sizeof(int);
	adjustPlace5(arr, arrLength);
	for (auto e : arr)
		cout << e << ' ';
	cout << endl;

	return 0;
}




























//使用STL算法实现，超级简单
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace::std;

bool isOdd(int x)
{
	return x % 2 != 0;
}

int main()
{
	int oddevne[] = { 1, 2, 3, 4, 5, 6 };
	int arrSize = sizeof(oddevne) / sizeof(int);
	stable_partition(oddevne, oddevne + arrSize, isOdd);
	copy(oddevne, oddevne + arrSize, ostream_iterator<int>(cout, " "));
	cout << endl;
	return 0;
}

/*
output:
1 5 3 4 2 6
这里原来数组的相对顺序变了
换成stable_partition(oddevne, oddevne + arrSize, &isOdd);
就可以了


stable_partition的输出：
1 3 5 2 4 6
*/

