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
����һ�ַ���
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
	int getCount(vector<int>& data, int begin, int end)  // ����data��Ҫ��&�������ô�ֵ  
	{
		if (begin >= end)
			return 0;      // �ݹ���ֹ���� 

		int mid = (begin + end) / 2;
		int lCount = getCount(data, begin, mid);   // �ݹ飬�鲢���򣬲����㱾���������   
		int rCount = getCount(data, mid + 1, end);

		vector<int> temp = data; // �������飬���ڹ鲢����  
		int forIdx = mid, backIdx = end, tempIdx = end;  // forIdx��ǰ�벿�ֵ��±꣬backIdx����벿�ֵ��±꣬tempIdx������������±�         
		int crossCount = 0;    // ��¼������������  

		while (forIdx >= begin && backIdx >= mid + 1)
		{
			if (data[forIdx] > data[backIdx])   // ���ڽ��������ԣ���ͳ��һ�£�Ȼ�����ν��ϴ�ֵ�Ž���������  
			{
				temp[tempIdx--] = data[forIdx--];
				crossCount += backIdx - mid;
			}
			else {
				temp[tempIdx--] = data[backIdx--];  // �����ڽ��������ԣ����ν��ϴ�ֵ�Ž���������   
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

// ����Ϊ���Բ���  
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

