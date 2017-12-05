/*
�ٶ�һ�ֱ���ı��뷶Χ��a-y��25����ĸ��
��1λ��4λ�ı��룬������ǰѸñ��밴�ֵ�������
�γ�һ���������£�
a,aa,aaa,aaaa,aaab,aaac,.....,....,
b,ba,baa,baaa,baab,baac,... ...,yyyw,yyyx,yyyy
����a��IndexΪ0��aa��IndexΪ1��aaa��IndexΪ2���Դ����ơ�
��дһ������������������һ�����룬�����������Ӧ��index���磺
���룺baca
�����16328
*/

/*
�о���Ŀ��Щ���⣬����baca�����Ӧ���ǣ�
a 0
aa 1
aaa 2
aaab 4
aaay
aab
aaba
aaby
aac
aacy
aad
aay
ab
aba
abaa

b 16276
*/

/*
���������2��ͬλ������֮��ľ��룬������base[4]�У�
base[4] = 1, ��aaaa��aaab֮�������
base[3] = base[4]*25+1����aaa��aab֮�������
base[2] = 25*base[3] + 1����aa��ab֮�������
base[1] = 25*base[2]+1����a��b֮�����
����һ���ַ����룬�Ӹ�λ���λɨ�衣
�Ե�iλ�ҳ���ͬλ���ģ���ǰ��i-1λ��ͬ��
�ҵ�iλ��a�ı���֮��ľ���
����baca��
��һ�����ҳ�b��λ�ã�����a֮��ľ���d1=(��b��-��a��)*base[1] + 1
�ڶ������ҳ�ba��λ�ã�����ba֮��ľ���d2 = (��a��-��a��)*base[2] + 1
���������ҳ�bac��λ�ã�����baa֮��ľ���d3 = (��c��-��a��)*base[3] + 1
���Ĳ����ҳ�baca��λ�ã�����baca֮��ľ���d4 = (��a��-��a��)*base[4] + 1
��baca��Index = d1+d2+d3+d4-1
*/

#include <iostream>  
#include <cstring> 

using namespace std;

int main()
{
	char str[1010];
	int base[4];
	base[3] = 1;
	for (int i = 2; i >= 0; i--)
		base[i] = base[i + 1] * 25 + 1;

	int index = 0;
	while (cin >> str) {
		int n = strlen(str);
		for (int j = 0; j < n; j++)
			index += ((str[j] - 'a')*base[j] + 1);
		cout << index - 1 << endl;//�����˼�1  
	}

	return 0;
}


//baca  
//16331  
//bc  
//33911  