/**************************************
题目：在数组中，数字减去它右边的数字得到一个数对之差。
求所有数对之差的最大值。
例如在数组{2, 4, 1, 16, 7, 5, 11, 9}中，
数对之差的最大值是11，是16减去5的结果。
***************************************/

int MaxDiff_Solution1(int numbers[], unsigned length)
{
	if (numbers == NULL || length < 2)
		return 0;

	int max, min;
	return MaxDiffCore(numbers, numbers + length - 1, &max, &min);
}

int MaxDiffCore(int* start, int* end, int* max, int* min)
{
	if (end == start)
	{
		*max = *min = *start;
		return 0x80000000;
	}

	int* middle = start + (end - start) / 2;

	int maxLeft, minLeft;
	int leftDiff = MaxDiffCore(start, middle, &maxLeft, &minLeft);

	int maxRight, minRight;
	int rightDiff = MaxDiffCore(middle + 1, end, &maxRight, &minRight);

	int crossDiff = maxLeft - minRight;

	*max = (maxLeft > maxRight) ? maxLeft : maxRight;
	*min = (minLeft < minRight) ? minLeft : minRight;

	int maxDiff = (leftDiff > rightDiff) ? leftDiff : rightDiff;
	maxDiff = (maxDiff > crossDiff) ? maxDiff : crossDiff;
	return maxDiff;
}