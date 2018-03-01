/*
ʱ�����ƣ�1��

�ռ����ƣ�100768K

һ���Ϸ�������ƥ�����б�����Ϊ:
1. �մ�""�ǺϷ�����������
2. ���"X"��"Y"�ǺϷ�������,��ô"XY"Ҳ��һ���Ϸ�����������
3. ���"X"��һ���Ϸ�������,��ô"(X)"Ҳ��һ���Ϸ�����������
4. ÿ���Ϸ����������ж�����������Ĺ�������
����"", "()", "()()()", "(()())", "(((()))"���ǺϷ��ġ�
��һ���ַ���S���Ƴ�������߶���ַ��õ������г�ΪS�������С�
����"abcde"����������"abe","","abcde"�ȡ�
����LCS(S,T)Ϊ�ַ���S���ַ���T����������еĳ���,
��һ���������W����S��������Ҳ��T�������еĳ��ȡ�
С�׸���һ���Ϸ�������ƥ������s,С��ϣ�������ҳ�����������������������t:
1��t��s��ͬ,���ǳ�����ͬ
2��tҲ��һ���Ϸ�������ƥ������
3��LCS(s, t)��������������������t������
��Ϊ������t���ܴ��ڶ��,С����Ҫ����������������t�ж��ٸ���

��������ʾ: s = "(())()",���ַ���s������ͬ�ĺϷ�����ƥ��������:
"()(())", "((()))", "()()()", "(()())",����LCS( "(())()", "()(())" )Ϊ4,
����������Ϊ5,�������3.
��������:
��������ַ���s(4 �� |s| �� 50,|s|��ʾ�ַ�������),��֤s��һ���Ϸ�������ƥ�����С�


�������:
���һ��������,����������t�ĸ�����

��������1:
(())()

�������1:
3
*/


#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

# define MAX_SIZE 100

using namespace std;

struct CountAndValue
{
	int count;
	int value;
};

int lcs(const string str1, const string str2)
{
	int len1 = str1.size();
	int len2 = str2.size();
	if (len1 == 0 || len2 == 0)
		return 0;
	vector<vector<int>> c(len1 + 1, vector<int>(len2 + 1, 0));
	for (int i = 1; i <= len1; ++i) {
		for (int j = 1; j <= len2; ++j) {
			if (str1[i - 1] == str2[j - 1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
			}
			else {
				c[i][j] = c[i][j - 1];
			}
		}
	}

	return c[len1][len2];
}

void _getParenthesis(int pos, int n, int open, int close, vector<string>& resultVec);

// Wrapper over _printParenthesis()
void getParenthesis(int n, vector<string>& resultVec)
{
	if (n > 0)
		_getParenthesis(0, n, 0, 0, resultVec);
	return;
}

void _getParenthesis(int pos, int n, int open, int close, vector<string>& resultVec)
{
	static char str[MAX_SIZE];

	if (close == n)
	{
		resultVec.push_back(str);
		//printf("%s \n", str);
		return;
	}
	else
	{
		if (open > close)
		{
			str[pos] = ')';
			_getParenthesis(pos + 1, n, open, close + 1, resultVec);
		}

		if (open < n)
		{
			str[pos] = '(';
			_getParenthesis(pos + 1, n, open + 1, close, resultVec);
		}
	}
}

int main()
{
	string s;// = "(((())))";
	cin >> s;
	int len = s.size();
	vector<string> vecStr;
	getParenthesis(len / 2, vecStr);
	vecStr.erase(remove(vecStr.begin(), vecStr.end(), s), vecStr.end());

	//for (int i = 0; i < vecStr.size(); ++i)
	//	cout << vecStr[i] << endl;

	vector<int> vecNum;
	for (int i = 0; i < vecStr.size(); ++i) {
		int temp = lcs(s, vecStr[i]);
		vecNum.push_back(temp);
	}
	sort(vecNum.begin(), vecNum.end());
	int resultNum = count(vecNum.begin(), vecNum.end(),
		vecNum[vecNum.size() - 1]);
	cout << resultNum << endl;

	return 0;
}

/*
���Ĵ����ѱ���
�ڴ泬��:���ĳ���ʹ���˳������Ƶ��ڴ�
caseͨ����Ϊ50.00%
*/























/*
�����⣬Ҫ��ʹ�� LCS ���
ɾȥ����һ���ַ����ɻ�� LCS = |s| - 1 ��
�ٰѸ��ַ��嵽��ԭ����ͬ������λ�ÿ���ά��ԭ���ȣ�
����Ӱ�� LCS �ļ��㡣
��������������ö��ÿ���ַ���
�������뵽����λ�ã��кϷ���ȥ�أ��ۼơ�

�Ż� 1 �������ǲ嵽ָ��λ�õ��ַ�֮ǰ��
���������ַ��͸�λ�õ��ַ���ͬ��
��������ԭ�ַ����������������������
�������Ľ��Ҫ - 1 ��
�Ż� 2 ����������һ�����������ţ�
�����ƶ����ǡ����ַ�ȴ���Բ嵽���ǵĺ��档
�кϷ���ʵ���Ͼ�������ƥ���ƽ���ԡ�
�����������Ǵ�ǰ���������
�����ſ�����ʱ���������ţ������������ڣ�
��Ϊ�ܹ��պ������ŵ������Ŷ�������ˡ�
ÿ�γɹ��պ�һ�����Ű����� - 1 ���õ�����˵����ƽ�⡣
*/
#include <stdio.h>
#include <algorithm>
#include <string>
#include <set>
#include <iostream>

using namespace std;

bool isLegal(const string& s)
{
	int cnt = 0;
	for (int i = 0; s[i]; ++i) {
		s[i] == '(' ? ++cnt : --cnt;
		if (cnt < 0) {
			return false;
		}
	}
	return true;
}

int main()
{
	string str;// = "((()))";
	cin >> str;
	set<string> record;
	for (int i = 1; i < str.size() - 1; ++i) {
		string tmp = str;
		tmp.erase(i, 1);
		for (int j = 1; j < str.size(); ++j) {
			if (str[i] == str[j]) 
				continue;
			string s(tmp);
			s.insert(j, 1, str[i]);
			if (isLegal(s)) {
				record.insert(s);
			}
		}
	}
	cout << record.size() << endl;

	return 0;
}