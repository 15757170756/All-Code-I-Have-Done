/*
ʱ�����ƣ�1��

�ռ����ƣ�32768K

Ϊ�˵õ�һ������"�෴��",���ǽ������������˳��ߵ�,
Ȼ���ټ���ԭ�ȵ����õ�"�෴��"������,Ϊ�˵õ�1325��"�෴��",
�������ǽ�����������˳��ߵ�,���ǵõ�5231,֮���ټ���ԭ�ȵ���,
���ǵõ�5231+1325=6556.����ߵ�֮���������ǰ׺��,ǰ׺�㽫�ᱻ���ԡ�
����n = 100, �ߵ�֮����1.
��������:
�������һ������n,(1 �� n �� 10^5)


�������:
���һ������,��ʾn���෴��

��������1:
1325

�������1:
6556
*/


#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace::std;

int main()
{
	int n;
	cin >> n;
	string str;
	int temp = n;
	while (temp) {
		char lastDigit = temp % 10 + '0';
		str.push_back(lastDigit);
		temp /= 10;
	}
	int inverseDigit = stoi(str);
	cout << n + inverseDigit << endl;

	return 0;
}


/*
���Ĵ����ѱ���
����ȷ:��ϲ�����ύ�ĳ���ͨ�������еĲ�������
*/