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
��������Ƚ�����
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
�������ڴ������Բ����ʾ��
����ͳ�Ƹ���ת��Ϊ��������1��
������Щ�ر�

-9����һλ��-5��������Դ�
�����Ĳ����ʾ���������
����-9�Ķ����Ʊ�ʾ��31��1
0xffff fff7,��Ϊ
1111 1111 1111 1111 1111 1111 1111 0111
-9��ԭ�룺1000 1001����Ϊ�Ǹ�����
���λΪ1������Ϊԭ��������λ
ȡ����1111 0110�������ټ�1
��1111 0111��Ȼ������һλΪ
��1111 1011��Ȼ��-1��ȡ��
��1111 0101��Ϊ-5
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