/*
http://www.cnblogs.com/plxx/p/3601329.html


C--全排列的实现(递归方法) 傻子也能看懂的



假设数组含有n个元素，则提取数组中的每一个元素做一次头元素，然后全排列除数组中除第一个元素之外的所有元素，这样就达到了对数组中所有元素进行全排列的得目的。【这句话才是重点！】

比如 1，2，3.的全排列就是分别以1，2，3开始的全排列。

　以1开始的全排列也就是2，3.的全排列，（2，3）的全排列就是分别以2和3开始的全排列。

 设全排列R(n1,n2,n3.....nn)，可以化简为分别以n1,n2,n3……开始的全排列。

 即   n1R1(n2,n3.....nn)，n2R2(n1,n3.....nn)，n3R3(n1,n2,.....nn)……nnR(n1,n2,n3.....)

 其中，R1(n2,n3.....nn)又可以按照R的方式继续进行……以此类推可以得到全排列。
 为方便起见，用123来示例下。123的全排列有123、132、213、231、312、321这六种。
 首先考虑213和321这二个数是如何得出的。显然这二个都是123中的1与后面两数交换得到的。
 然后可以将123的第二个数和每三个数交换得到132。同理可以根据213和321来得231和312。
 因此可以知道——全排列就是从第一个数字起每个数分别与它后面的数字交换。
 找到这个规律后，递归的代码就很容易写出来了：

 */

#include <iostream>
#include <algorithm>
#include <iterator>

using namespace::std;

void perm(int list[], int start, int listLen)
{
	if (start == listLen)
	{
		copy(list, list + listLen, ostream_iterator<int>(cout, " "));
		cout << endl;
		return;
	}
	for (int i = start; i < listLen; i++)
	{
		if (list[start] != list[i])
			swap(list[start], list[i]);
		perm(list, start + 1, listLen);
		if (list[start] != list[i])
			swap(list[start], list[i]);
	}
}


int main()
{
	int arr[] = { 1, 2, 3, 4 };
	perm(arr, 0, 4);

	return 0;
}