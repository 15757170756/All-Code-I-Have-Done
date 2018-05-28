#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <stack>
#include <queue>
#include <functional>
#include <cmath>

using namespace::std;

void computePrefixFunction(string &patten, vector<int> &next)
{
	int len = patten.size();
	next.assign(len, 0);
	int k = 0;
	for (int q = 1; q < len; ++q) {
		while (k > 0 && patten[k] != patten[q])
			k = next[k - 1];
		if (patten[k] == patten[q])
			++k;
		next[q] = k;
	}
}

int KMP(string &text, string &patten)
{
	int textLen = text.size();
	int pattenLen = patten.size();
	vector<int> next;
	computePrefixFunction(patten, next);
	int q = 0;
	for (int i = 0; i < textLen; ++i) {
		while (q > 0 && patten[q] != text[i])
			q = next[q - 1];
		if (patten[q] == text[i])
			++q;
		if (q == pattenLen)
			return i + 1 - pattenLen;
	}

	return -1;
}


int partion(int arr[], int low, int high)
{
	int pivotKey = arr[low];
	while (low < high) {
		while (low < high && arr[high] >= pivotKey)
			--high;
		arr[low] = arr[high];
		while (low < high && arr[low] <= pivotKey)
			++low;
		arr[high] = arr[low];
	}
	arr[low] = pivotKey;
	return low;
}

void quickSort(int arr[], int low, int high)
{
	if (low >= high)
		return;

	int pivotPos = partion(arr, low, high);
	quickSort(arr, low, pivotPos - 1);
	quickSort(arr, pivotPos + 1, high);
}

void testQuickSort()
{
	cout << "testQuickSort:\n";
	int arr[] = { 3, 2, 4, 1, 5 };
	int n = sizeof(arr) / sizeof(arr[0]);
	for (int e : arr)
		cout << e << ' ';
	cout << endl;
	quickSort(arr, 0, n - 1);
	for (int e : arr)
		cout << e << ' ';
	cout << endl;
}

void merge(int arr[], int start, int mid, int end)
{
	int leftNum = mid - start + 1;
	int rightNum = end - mid;
	int *leftArr = new int[leftNum];
	int *rightArr = new int[rightNum];

	for (int i = 0; i < leftNum; ++i)
		leftArr[i] = arr[start + i];
	for (int i = 0; i < rightNum; ++i)
		rightArr[i] = arr[mid + 1 + i];

	int k = start;
	int i = 0, j = 0;
	while (i < leftNum && j < rightNum) {
		if (leftArr[i] < rightArr[j])
			arr[k++] = leftArr[i++];
		else
			arr[k++] = rightArr[j++];
	}
	while (i < leftNum)
		arr[k++] = leftArr[i++];
	while (j < rightNum)
		arr[k++] = rightArr[j++];

	delete[] leftArr;
	delete[] rightArr;
}

void mergeSort(int arr[], int start, int end)
{
	if (start < end) {
		int mid = (start + end) / 2;
		mergeSort(arr, start, mid);
		mergeSort(arr, mid + 1, end);
		merge(arr, start, mid, end);
	}
}

void testMergeSort()
{
	cout << "testMergeSort:\n";
	int arr[] = { 3, 2, 4, 1, 5 };
	int n = sizeof(arr) / sizeof(arr[0]);
	for (int e : arr)
		cout << e << ' ';
	cout << endl;
	mergeSort(arr, 0, n - 1);
	for (int e : arr)
		cout << e << ' ';
	cout << endl;
}

void heapify(int arr[], int n, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left < n && arr[left] > arr[largest])
		largest = left;
	if (right < n && arr[right] > arr[largest])
		largest = right;
	if (largest != i) {
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}

void heapSort(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; --i)
		heapify(arr, n, i);
	for (int i = n - 1; i >= 0; --i) {
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

void testHeapSort()
{
	cout << "testHeapSort:\n";
	int arr[] = { 3, 2, 4, 1, 5 };
	int n = sizeof(arr) / sizeof(arr[0]);
	for (int e : arr)
		cout << e << ' ';
	cout << endl;
	heapSort(arr, n);
	for (int e : arr)
		cout << e << ' ';
	cout << endl;
}

int main(int argc, char* argv[])
{
	testQuickSort();
	testMergeSort();
	testHeapSort();
}

