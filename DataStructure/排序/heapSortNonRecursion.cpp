/*
Name:
Copyright:
Author:licf
Date:
Description:∂—≈≈–ÚC++”Ô—‘ µœ÷
*/
// C++ program for implementation of Heap Sort
#include <iostream>
using namespace std;

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
void heapify(int arr[], int n, int i)
{
	while (i < n) {
		int largest = i; // Initialize largest as root
		int l = 2 * i + 1; // left = 2*i + 1
		int r = 2 * i + 2; // right = 2*i + 2

		// If left child is larger than root
		if (l < n && arr[l] > arr[largest])
			largest = l;

		// If right child is larger than largest so far
		if (r < n && arr[r] > arr[largest])
			largest = r;

		// If largest is not root
		if (largest != i) {
			swap(arr[i], arr[largest]);
			i = largest;
			// Recursively heapify the affected sub-tree
		}
		else
			break;
	}
}

// main function to do heap sort
void heapSort(int arr[], int n)
{
	// Build heap (rearrange array)
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// One by one extract an element from heap
	for (int i = n - 1; i >= 0; i--)
	{
		// Move current root to end
		swap(arr[0], arr[i]);

		// call max heapify on the reduced heap
		heapify(arr, i, 0);
	}
}

/* A utility function to print array of size n */
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; ++i)
		cout << arr[i] << " ";
	cout << "\n";
}

// Driver program
int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	int n = sizeof(arr) / sizeof(arr[0]);

	printf("Unorted array is:");
	printArray(arr, n);
	printf("\n");

	heapSort(arr, n);

	printf("Sorted array is:");
	printArray(arr, n);
	printf("\n");
}











/*
Name:
Copyright:
Author:licf
Date:
Description:∂—≈≈–ÚC”Ô—‘ µœ÷
*/
// C implementation of Heap Sort
#include <stdio.h>
#include <stdlib.h>

// A heap has current size and array of elements
struct MaxHeap
{
	int size;
	int* array;
};

// A utility function to swap to integers
void swap(int* a, int* b) { int t = *a; *a = *b;  *b = t; }

// The main function to heapify a Max Heap. The function
// assumes that everything under given root (element at
// index idx) is already heapified
void maxHeapify(struct MaxHeap* maxHeap, int idx)
{
	while (idx < maxHeap->size) {
		int largest = idx;  // Initialize largest as root
		int left = (idx << 1) + 1;  // left = 2*idx + 1
		int right = (idx + 1) << 1; // right = 2*idx + 2

		// See if left child of root exists and is greater than
		// root
		if (left < maxHeap->size &&
			maxHeap->array[left] > maxHeap->array[largest])
			largest = left;

		// See if right child of root exists and is greater than
		// the largest so far
		if (right < maxHeap->size &&
			maxHeap->array[right] > maxHeap->array[largest])
			largest = right;

		// Change root, if needed
		if (largest != idx)
		{
			swap(&maxHeap->array[largest], &maxHeap->array[idx]);
			idx = largest;
		}
		else
			break;
	}
}

// A utility function to create a max heap of given capacity
struct MaxHeap* createAndBuildHeap(int *array, int size)
{
	int i;
	struct MaxHeap* maxHeap =
		(struct MaxHeap*) malloc(sizeof(struct MaxHeap));
	maxHeap->size = size;   // initialize size of heap
	maxHeap->array = array; // Assign address of first element of array

	// Start from bottommost and rightmost internal mode and heapify all
	// internal modes in bottom up way
	for (i = (maxHeap->size - 2) / 2; i >= 0; --i)
		maxHeapify(maxHeap, i);
	return maxHeap;
}

// The main function to sort an array of given size
void heapSort(int* array, int size)
{
	// Build a heap from the input data.
	struct MaxHeap* maxHeap = createAndBuildHeap(array, size);

	// Repeat following steps while heap size is greater than 1.
	// The last element in max heap will be the minimum element
	while (maxHeap->size > 1)
	{
		// The largest item in Heap is stored at the root. Replace
		// it with the last item of the heap followed by reducing the
		// size of heap by 1.
		swap(&maxHeap->array[0], &maxHeap->array[maxHeap->size - 1]);
		--maxHeap->size;  // Reduce heap size

		// Finally, heapify the root of tree.
		maxHeapify(maxHeap, 0);
	}
}

// A utility function to print a given array of given size
void printArray(int* arr, int size)
{
	int i;
	for (i = 0; i < size; ++i)
		printf("%d ", arr[i]);
}

/* Driver program to test above functions */
int main()
{
	int arr[] = { 7, 6, 5, 4, 3, 2, 1, 9 };
	int size = sizeof(arr) / sizeof(arr[0]);
	printf("Unorted array is:");
	printArray(arr, size);
	printf("\n");

	heapSort(arr, size);

	printf("Sorted array is:");
	printArray(arr, size);
	printf("\n");

	return 0;
}
