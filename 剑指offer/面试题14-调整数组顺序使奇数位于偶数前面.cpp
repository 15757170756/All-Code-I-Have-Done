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
��ָoffer�Ĵ�
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
��չ�Խⷨ��
���ú���ָ�������ж�
��������㷨�е�lambda����
���㺯��ָ��ķ���ǰ�棬
������ķ��ں���
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
���磺��3�ı�������ǰ�棬
����3�ı������ں���
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