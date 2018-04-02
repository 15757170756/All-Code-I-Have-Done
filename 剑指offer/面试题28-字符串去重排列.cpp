/*
二、去掉重复的全排列的递归实现
由于全排列就是从第一个数字起每个数分别与它后面的数字交换。我们先尝试加个这样的判断——如果一个数与后面的数字相同那么这二个数就不交换了。如122，第一个数与后面交换得212、221。然后122中第二数就不用与第三个数交换了，但对212，它第二个数与第三个数是不相同的，交换之后得到221。与由122中第一个数与第三个数交换所得的221重复了。所以这个方法不行。

换种思维，对122，第一个数1与第二个数2交换得到212，然后考虑第一个数1与第三个数2交换，此时由于第三个数等于第二个数，所以第一个数不再与第三个数交换。再考虑212，它的第二个数与第三个数交换可以得到解决221。此时全排列生成完毕。
这样我们也得到了在全排列中去掉重复的规则——去重的全排列就是从第一个数字起每个数分别与它后面非重复出现的数字交换。下面给出完整代码：
*/

#include<iostream>  
using namespace std;
#include<assert.h>  

//在[nBegin,nEnd)区间中是否有字符与下标为pEnd的字符相等  
bool IsSwap(char* pBegin, char* pEnd)
{
	char *p;
	for (p = pBegin; p < pEnd; p++)
	{
		if (*p == *pEnd)
			return false;
	}
	return true;
}
void Permutation(char* pStr, char *pBegin)
{
	assert(pStr);

	if (*pBegin == '\0')
	{
		static int num = 1;  //局部静态变量，用来统计全排列的个数  
		printf("第%d个排列\t%s\n", num++, pStr);
	}
	else
	{
		for (char *pCh = pBegin; *pCh != '\0'; pCh++)   //第pBegin个数分别与它后面的数字交换就能得到新的排列     
		{
			if (IsSwap(pBegin, pCh))
			{
				swap(*pBegin, *pCh);
				Permutation(pStr, pBegin + 1);
				swap(*pBegin, *pCh);
			}
		}
	}
}

int main(void)
{
	char str[] = "baa";
	Permutation(str, str);
	return 0;
}