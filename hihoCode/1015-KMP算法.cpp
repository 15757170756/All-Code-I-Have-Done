/*ʱ������:1000ms
����ʱ�� : 1000ms
�ڴ����� : 256MB
����
СHi��СHo��һ�Ժ����ѣ���������Ϣ���������ǶԱ�̲�����Ī�����Ȥ��
����Լ���û���������ڱ�̵�ѧϰ��·��һͬǰ����

��һ�죬����������һֻ��з�����Ǻ�з����СHi��СHo������Ǹ���������⣺
��СHi��СHo�������ܲ��ܹ��ж�һ�����֣�ԭ���������ǲ��Ǵ�����ôһЩ�������⡭�������֣�ģʽ��������

СHi��СHo��ϸ˼����һ�£�����ֻ���뵽�ܼ򵥵�������
�����־��ü�Ȼ��з������ô˵�ˣ��Ϳ϶�������ô���׵������ǻش��ˣ�
��������ֻ��˵��������Ǹ����з����������ֻ���뵽ʱ�临�Ӷ�Ϊ���ı����� * ���������ܳ��ȣ��ķ�����
������ÿ��ģʽ���ֿ��жϣ�Ȼ������ö����ʼλ�ò�����Ƿ��ܹ�ƥ�䣬�����ⲻ������Ҫ�ķ����ǰɣ���

��з���˵�ͷ��˵�������������ǵ�ˮƽ���д���ߣ������ɣ�
�����˵ֻ��һ���������֣����ܲ��������أ���

СHo��ʱ���е����κ����ģ�����СHi�ܿ쿪�ڵ���
����֪���������һ���ܾ����ģʽƥ�����⣡����ʹ��KMP�㷨������⣡��

��з����ĵ��˵�ͷ����СHi˵��������Ȼ��֪���ͺð��ˣ�
��ȥ��СHo�̻ᣬ����������Ҫ�����񽻸����ǣ���

����֤������񣡡�СHi��ͷ����

��ʾһ��KMP��˼·

��ʾ����NEXT�����ʹ��

��ʾ����������NEXT����

����
��һ��һ������N����ʾ��������������

��������N * 2�У�ÿ���б�ʾһ���������ݡ���ÿһ�����������У�
��һ��Ϊģʽ�����ɲ�����10 ^ 4����д��ĸ��ɣ��ڶ���Ϊԭ�����ɲ�����10 ^ 6����д��ĸ��ɡ�

����N <= 20

���
����ÿһ���������ݣ����������������г��ֵ�˳�����һ��Ans����ʾģʽ����ԭ���г��ֵĴ�����

��������
5
HA
HAHAHA
WQN
WQN
ADA
ADADADA
BABABB
BABABABABABABABABB
DAD
ADDAADAADDAAADAAD
�������
3
1
3
1
0
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int* compute_prefix_function(string patten);
int KMP_match(string text, string patten);


int main(int argc, char* argv[])
{
	int N;
	cin >> N;
	string oriStr, pattenStr;
	vector<string> oriStrVec, pattenStrVec;
	while (N > 0) {
		cin >> pattenStr;
		pattenStrVec.push_back(pattenStr);
		cin >> oriStr;
		oriStrVec.push_back(oriStr);
		--N;
	}
	for (int i = 0; i < pattenStrVec.size(); ++i)
		cout << KMP_match(oriStrVec[i], pattenStrVec[i]) << endl;;

	return 0;
}


/*
����next����
ababaca��next����Ϊ��
0012302
��ǰ�ַ���ǰ���ַ����
���ǰ׺���׺ƥ��
*/
int* compute_prefix_function(string patten)
{
	int m = patten.size();
	int* next = new int[m];
	next[0] = 0;
	int k = 0;
	for (int q = 1; q < m; ++q) {
		while (k > 0 && patten[k] != patten[q])
			k = next[k - 1];
		if (patten[k] == patten[q])
			k++;
		next[q] = k;
	}
	return next;
}

int KMP_match(string text, string patten)
{
	int count = 0;
	int n = text.size();
	int m = patten.size();
	int* next = compute_prefix_function(patten);
	int q = 0;
	for (int i = 0; i < n; ++i) {
		while (q > 0 && patten[q] != text[i])
			q = next[q - 1];
		if (patten[q] == text[i])
			q++;
		if (q == m) {
			++count;
		}
	}
	delete[] next;
	next = NULL;
	return count;
}