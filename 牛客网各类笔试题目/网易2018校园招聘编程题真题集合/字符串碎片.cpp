/*
ʱ�����ƣ�1��

�ռ����ƣ�32768K

һ����Сд��ĸ��ɵ��ַ������Կ���һЩͬһ��ĸ�������Ƭ��ɵġ�
����,"aaabbaaac"����������Ƭ��ɵ�:'aaa','bb','c'��
ţţ���ڸ���һ���ַ���,���������������ַ�����������Ƭ��ƽ�������Ƕ��١�

��������:
�������һ���ַ���s,�ַ���s�ĳ���length(1 �� length �� 50),sֻ��Сд��ĸ('a'-'z')


�������:
���һ������,��ʾ������Ƭ��ƽ������,�������뱣����λС����

��������ʾ: s = "aaabbaaac"
������Ƭ��ƽ������ = (3 + 2 + 3 + 1) / 4 = 2.25

��������1:
aaabbaaac

�������1:
2.25
*/



#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace::std;

int main()
{
	string s;
	cin >> s;
	vector<int> substrLen;

	for (int i = 0; i < s.size();) {
		int cnt = 0;
		for (int j = i; j < s.size(); ++j) {
			if (s[j] == s[j + 1])
				++cnt;
			else
				break;
		}
		substrLen.push_back(cnt + 1);
		i += (cnt + 1);
	}

	double aver = 0;
	for (int i = 0; i < substrLen.size(); ++i)
		aver += substrLen[i];
	aver = aver / substrLen.size();
	cout.setf(ios::fixed);
	cout << setprecision(2) << aver << endl;
	return 0;
}

/*
���Ĵ����ѱ���
����ȷ:��ϲ�����ύ�ĳ���ͨ�������еĲ�������
*/