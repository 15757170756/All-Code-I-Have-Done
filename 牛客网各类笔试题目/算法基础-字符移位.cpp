/*
ʱ�����ƣ�1��

�ռ����ƣ�32768K

СQ���������һ�����⣺��һ���ַ����Ĵ�д��ĸ�ŵ��ַ����ĺ��棬
�����ַ������λ�ò��䣬�Ҳ����������Ŀռ䡣
���ܰ��СQ��


��������:

���������ж��飬ÿ�����һ���ַ���s���ұ�֤:1<=s.length<=1000.

�������:

����ÿ�����ݣ������λ����ַ�����


��������1:
AkleBiCeilD

�������1:
kleieilABCD
*/


/*
����ˢ��ָoffer���������õģ�
�������STL �Ľⷨ�ǿ��˳�˶�Ĺ��������̵�
����棬�Ȿ����Ȼ��Щ��������ҵ��
���Ƕ��ҵȻ�����Ļ������õġ�
*/
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string.h>

using namespace::std;

bool isUpper(char ch)
{
	return !(ch >= 'A' && ch <= 'Z');
}

int main()
{
	char str[1000];// = "AkleBiCeilD";
	while (cin >> str) {
		int strLen = strlen(str);
		stable_partition(str, str + strLen, isUpper);
		cout << str << endl;
	}

	return 0;
}