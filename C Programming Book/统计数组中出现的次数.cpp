/*
http://blog.csdn.net/bluetears1988/article/details/12383319

8.给定数组A，大小为N，数字元素为1~N的int数，但是有些数字出现多次，
有些数字没出现，统计出哪些数字出现了多次，哪些数字没有出现，
要求额外空间使用O(1)，时间O(N)

答：空间复杂度为o(1),故不能用额外的空间，即在数组本身上操作。时间为o(N),
故不能用先排序后比较相邻元素的方法，时间为o(nlogn)。

先采用元素交换法，使数组下标=数组中元素值 - 1，如果元素A[i]存在多个，
则在其他位置还存在A[j]=A[i]，i<>j，将正确的位置下的值置为-1。
然后遍历数组统计次数。如有A[j]=A[i]，i<>j的情况，
则将满足A[A[i]-1]=A[i]的值减1，然后令A[j]=0。
如果数组中元素重复出现多次，则数组的值<-1；如果只出现一次，
则值等于-1；如果一次都没出现，则值为0。再扫描一遍数组，可以得到元素出现次数。
*/

void swap(int *a, int len)
{
	int i, j;
	for (i = 0; i < len; i++)
	{
		j = a[i];
		while (i != (j - 1) && a[j - 1] != j)
		{
			a[i] = a[j - 1];
			a[j - 1] = j;
			j = a[i];
		}
		/*      if(i == (j-1) || a[j-1] = j )
		continue;
		a[i] = a[j-1];
		a[j-1] = j;
		i--;
		*/
	}
}

void count(int *a, int len)
{
	int i, j;
	for (i = 0; i < len; i++)
	{
		j = a[i];
		if (i == (j - 1))
		{
			a[i] = -1;
		}
		else
		{
			a[j] -= 1;
			j = 0;
		}
	}

	for (i = 0; i< len; i++)
	{
		if (a[i] == 0)
		{
			printf("%d没有在数组中出现"，i);
		}
		else if (a[i] == -1)
		{
			printf("%d在数组中出现一次"，i);
		}
		else
		{
			printf("%d在数组中出现了多次"，i);
		}
	}
}