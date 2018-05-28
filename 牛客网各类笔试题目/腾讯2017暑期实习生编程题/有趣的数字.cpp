/*
ʱ�����ƣ�1��
�ռ����ƣ�32768K

СQ�������ϲ���ʱ�뵽��������⣺��n������
������ɶ�Ԫ�飬����С���ж��ٶ��أ�������أ�
��������:
�����������������ݡ�
����ÿ��������ݣ�
N - �������������n����
a1,a2...an - ��Ҫ���������
��֤:
1<=N<=100000,0<=ai<=INT_MAX.
�������:
����ÿ�����ݣ��������������һ������ʾ����С�Ķ�����
�ڶ�������ʾ�����Ķ�����
��������1:
6
45 12 45 32 5 6
�������1:
1 2
*/


/*
�Ҿ��������Ŀ�Ŀ����ڡ��������������������ݡ�
��ȻҲ����̫��רҵ�ˣ���Ϊ����������ݣ�����
���������ʱ��һ���÷���whileѭ�����
����vector<int> vec;�������whileѭ������
�����ᵼ��vecһֱ�ڼ����ݣ�����϶����ԡ�
���������Ŀ������˵�Ƚϼ򵥡�
*/


#include <algorithm>
#include <vector>
#include <iostream>

using namespace::std;

int main()
{
	int n;
	while (cin >> n) {
		int pairOfMaxNum = 0, pairOfMinNum = 0;
		int temp;
		vector<int> vec;
		for (int i = 0; i < n; ++i) {
			cin >> temp;
			vec.emplace_back(temp);
		}

		sort(vec.begin(), vec.end());
		int minNum = vec[0], maxNum = vec[n - 1];
		int minCnt = count(vec.begin(), vec.end(), minNum);
		int maxCnt = count(vec.begin(), vec.end(), maxNum);
		pairOfMaxNum = minCnt * maxCnt;

		vector<int> vecDiff;
		for (int i = 0; i < n - 1; ++i) {
			int diff = vec[i + 1] - vec[i];
			vecDiff.emplace_back(diff);
		}

		sort(vecDiff.begin(), vecDiff.end());

		int minDiffNum = vecDiff[0];
		if (0 == minDiffNum) {
			for (int i = 1; i < n; ++i) {
				int j = i - 1;
				while (j >= 0 && vec[j] == vec[i]) {
					++pairOfMinNum;
					--j;
				}
			}
		}

		else {
			pairOfMinNum = count(vecDiff.begin(),
				vecDiff.end(), vecDiff[0]);
		}

		cout << pairOfMinNum << ' ' << pairOfMaxNum << endl;
	}

	return 0;
}