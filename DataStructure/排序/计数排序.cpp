//C Program for counting sort
#include <stdio.h>
#include <string.h>
#define RANGE 255

// The main function that sort the given string arr[] in
// alphabatical order
void countSort(char arr[])
{
	// The output character array that will have sorted arr
	char* output = new char[strlen(arr)];
	// Create a count array to store count of inidividul
	// characters and initialize count array as 0
	int count[RANGE + 1], i;
	memset(count, 0, sizeof(count));

	// Store count of each character
	for (i = 0; arr[i]; ++i)
		++count[arr[i]];

	// Change count[i] so that count[i] now contains actual
	// position of this character in output array
	for (i = 1; i <= RANGE; ++i)
		count[i] += count[i - 1];

	// Build the output character array
	for (i = 0; arr[i]; ++i)
	{
		output[count[arr[i]] - 1] = arr[i];
		--count[arr[i]];
	}

	// Copy the output array to arr, so that arr now
	// contains sorted characters
	for (i = 0; arr[i]; ++i)
		arr[i] = output[i];

	delete[] output;
}

// Driver program to test above function
int main()
{
	char arr[] = "geeksforgeeks";//"applepp";

	countSort(arr);

	printf("Sorted character array is %sn", arr);
	return 0;
}










#include <iostream>
#include <vector>
using namespace::std;

int main()
{
	int k = 10;
	vector<int> arr = { 10, 9, 5, 2, 4, 1, 2, 7, 8, 9, 3, 0, 9, 8 };
	int arrLength = arr.size();
	vector<int> output(arrLength);
	vector<int> count(k + 1);
	for (int i = 0; i < arrLength; ++i)
		++count[arr[i]];
	for (int i = 1; i < k + 1; ++i)
		count[i] += count[i - 1];
	for (int i = 0; i < arrLength; ++i) {
		output[count[arr[i]] - 1] = arr[i];
		--count[arr[i]];
	}
	for (int i = 0; i < arrLength; ++i)
		cout << output[i] << endl;
}