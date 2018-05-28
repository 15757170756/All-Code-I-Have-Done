#include <iostream>
#include <cstring>
#include <cmath>

using namespace::std;

int NumberOf11(int n)
{
	int count = 0;
	while (n) {
		if (n & 1 == 1)
			++count;
		n = n >> 1;
	}
	return count;
}

int NumberOf12(int n)
{
	int count = 0;
	unsigned int flag = 1;
	while (flag) {
		if (n & flag)
			++count;
		flag = flag << 1;
	}
	return count;
}


/*
这个方法比较巧妙
*/
int NumberOf13(int n)
{
	int count = 0;
	while (n) {
		++count;
		n = (n - 1) & n;
	}
	return count;
}

/*
负数在内存中是以补码表示的
所以统计负数转化为二进制中1的
个数有些特别

-9右移一位是-5，这个可以从
整数的补码表示计算出来，
所以-9的二进制表示有31个1
0xffff fff7,即为
1111 1111 1111 1111 1111 1111 1111 0111
-9的原码：1000 1001，因为是负数，
最高位为1，反码为原码除了最高位
取反：1111 0110，补码再加1
：1111 0111，然后右移一位为
：1111 1011，然后-1再取反
：1111 0101，为-5
*/

int BitLength(unsigned int n)
{
	int c = 0;  // counter
	while (n)
	{
		++c;
		n >>= 1;
	}
	return c;
}
int main()
{
	int n = -1234;
	int cnt = NumberOf12(n);
	cout << cnt << endl;
	cnt = NumberOf13(n);
	cout << cnt << endl;

	return 0;
}

struct LinkNode 
{ int val; 
	struct LinkNode * next;
}; 
struct LinkNode *insert(LinkNode * head, LinkNode * node)
{

}