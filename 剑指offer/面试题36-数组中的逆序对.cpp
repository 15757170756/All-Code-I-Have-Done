#include <stdio.h>
#include <stdlib.h>

int inversePairs(int* data, int length);
int inversePairsCore(int* data, int* copy, int start, int end);

int main()
{
	int a[] = { 4, 3, 5, 2, 1, -2, 9, 7 };
	int arrLength = sizeof(a) / sizeof(int);
	int count = inversePairs(a, arrLength);
	printf("inversePairs count : %d\n", count);

	return 0;
}


int inversePairs(int* data, int length)
{
	if (data == NULL || length < 0)
		return 0;
	int* copy = (int*)malloc(length*sizeof(int));
	for (int i = 0; i < length; ++i)
		copy[i] = data[i];
	int count = inversePairsCore(data, copy, 0, length - 1);
	delete[] copy;
	return count;
}

int inversePairsCore(int* data, int* copy, int start, int end)
{
	if (start == end) {
		copy[start] = data[start];
		return 0;
	}
	int length = (end - start) / 2;
	int left = inversePairsCore(copy, data, start, start + length);
	int right = inversePairsCore(copy, data, start + length + 1, end);

	int i = start + length;
	int j = end;
	int indexCopy = end;
	int count = 0;
	while (i >= start && j >= start + length + 1) {
		if (data[i] > data[j]) {
			copy[indexCopy--] = data[i--];
			count += j - start - length;
		}
		else
			copy[indexCopy--] = data[j--];
	}
	while (i >= start)
		copy[indexCopy--] = data[i--];
	while (j >= start + length + 1)
		copy[indexCopy--] = data[j--];

	return left + right + count;
}













/*
使用归并排序方法
http://blog.csdn.net/acdreamers/article/details/16849761
我们知道,求逆序对最典型的方法就是树状数组，但是还有一种方法就是Merge_sort(),即归并排序。

实际上归并排序的交换次数就是这个数组的逆序对个数，为什么呢？

我们可以这样考虑：
归并排序是将数列a[l,h]分成两半a[l,mid]和a[mid+1,h]分别进行归并排序，
然后再将这两半合并起来。
在合并的过程中（设l<=i<=mid，mid+1<=j<=h），当a[i]<=a[j]时，
并不产生逆序数；当a[i]>a[j]时，在
前半部分中比a[i]大的数都比a[j]大，将a[j]放在a[i]前面的话，
逆序数要加上mid+1-i。因此，可以在归并
排序中的合并过程中计算逆序数.

题目:http://poj.org/problem?id=1804

题意:给定一个序列a[],每次只允许交换相邻两个数,最少要交换多少次才能把它变成非递降序列.


*/


#include <iostream>

using namespace::std;

const int N = 1005;

int a[N], tmp[N];
int ans;

void Merge(int left, int mid, int right)
{
	int i = left;
	int j = mid + 1;
	int k = left;
	while (i <= mid&&j <= right) {
		if (a[i] > a[j]) {
			tmp[k++] = a[j++];
			ans += mid - i + 1;
		}
		else
			tmp[k++] = a[i++];
	}
	while (i <= mid)
		tmp[k++] = a[i++];
	while (j <= right)
		tmp[k++] = a[j++];

	for (int i = left; i <= right; ++i)
		a[i] = tmp[i];
}

void mergeSort(int left, int right)
{
	if (left < right) {
		int mid = (left + right) >> 1;
		mergeSort(left, mid);
		mergeSort(mid + 1, right);
		Merge(left, mid, right);
	}
}

int main()
{
	int n, T, tt = 1;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		ans = 0;
		mergeSort(0, n - 1);
		printf("Scenario #%d:\n%d\n\n", tt++, ans);
	}
	return 0;
}














/*
另外一种方法
*/
#include<cstdio>  
#include<vector> 

using namespace std;

class Solution {
public:
	int InversePairs(vector<int> data)
	{
		int len = data.size();
		if (len == 0)
			return 0;
		return getCount(data, 0, len - 1);
	}
	int getCount(vector<int>& data, int begin, int end)  // 这里data需要用&进行引用传值  
	{
		if (begin >= end)
			return 0;      // 递归终止条件 

		int mid = (begin + end) / 2;
		int lCount = getCount(data, begin, mid);   // 递归，归并排序，并计算本次逆序对数   
		int rCount = getCount(data, mid + 1, end);

		vector<int> temp = data; // 辅助数组，用于归并排序  
		int forIdx = mid, backIdx = end, tempIdx = end;  // forIdx：前半部分的下标，backIdx：后半部分的下标，tempIdx：辅助数组的下标         
		int crossCount = 0;    // 记录交叉的逆序对数  

		while (forIdx >= begin && backIdx >= mid + 1)
		{
			if (data[forIdx] > data[backIdx])   // 存在交叉的逆序对，先统计一下，然后依次将较大值放进辅助数组  
			{
				temp[tempIdx--] = data[forIdx--];
				crossCount += backIdx - mid;
			}
			else {
				temp[tempIdx--] = data[backIdx--];  // 不存在交叉的逆序对，依次将较大值放进辅助数组   
			}
		}

		while (forIdx >= begin)
			temp[tempIdx--] = data[forIdx--];
		while (backIdx >= mid + 1)
			temp[tempIdx--] = data[backIdx--];
		for (int i = begin; i <= end; i++)
			data[i] = temp[i];

		return (lCount + rCount + crossCount);
	}
};

// 以下为测试部分  
int main()
{
	Solution sol;
	vector<int> vec1 = { 8, 4, 2, 7, 6, 2 };
	vector<int> vec2 = { 1, 2, 3, 9, 8, 7, 6 };
	vector<int> vec3 = { 7, 5, 6, 4 };
	int num1 = sol.InversePairs(vec1);
	int num2 = sol.InversePairs(vec2);
	int num3 = sol.InversePairs(vec3);

	printf("%d\n", num1);
	printf("%d\n", num2);
	printf("%d\n", num3);
	return 0;
}

