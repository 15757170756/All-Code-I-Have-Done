/*ʱ������:10000ms
����ʱ�� : 1000ms
�ڴ����� : 256MB
����
СHi��СHo����һ����Ϸ������һ������A = [A1, A2, ... AN]��СHi����ָ��M����ͬ��ֵS1��S2, S3 ... SM��
���������ܵ÷��� ��Si �� count(Si)����count(Si)����������Si��ȵ�Ԫ�صĸ���)��
Ϊ�������Ѷȣ�СHoҪ��СHiѡ���S1..SM������������Si��Sj������ | Si - Sj | > 1��
���ܰ���СHi��������÷��Ƕ�����
����
��һ�а�����������N��M��
�ڶ��а���N������A1, A2, ... AN��
����30%�����ݣ�1 �� M �� N �� 10
����100%�����ݣ�1 �� M �� N �� 1000 1 �� Ai �� 100000
���
���÷�
��������
5 2
1 2 1 2 3
�������
5
*/

/*
�Լ�д��
��ʱ��
*/


#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace::std;

template<typename T>
void combinations(const vector<T> &v, size_t count, vector<vector<int>> &resultVec)
{
	assert(count <= v.size());
	vector<bool> bitset(v.size() - count, 0);
	bitset.resize(v.size(), 1);
	do {
		vector<int> temp;
		temp.clear();
		for (size_t i = 0; i != v.size(); ++i) {
			if (bitset[i]) {
				temp.push_back(v[i]);
				//cout << v[i] << " ";
			}
		}
		sort(temp.begin(), temp.end());
		int count = 0;
		for (int i = 0; i < temp.size() - 1; ++i) {
			if (abs(temp[i] - temp[i + 1]) > 1)
				++count;
		}
		if (count == temp.size() - 1)
			resultVec.push_back(temp);
		//cout << endl;
		//for (int i = 0; i < bitset.size(); ++i)
		//	cout << bitset[i] << " ";
		//cout << endl;
	} while (next_permutation(bitset.begin(), bitset.end()));

	auto last = unique(resultVec.begin(), resultVec.end());
	resultVec.erase(last, resultVec.end());
}


int main()
{
	int N, M;
	cin >> N >> M;
	vector<int> v;
	int temp;
	for (int i = 0; i < N; ++i) {
		cin >> temp;
		v.push_back(temp);
	}
	vector<vector<int>> combiResultVec;
	combinations(v, M, combiResultVec);
	for (int i = 0; i < combiResultVec.size(); ++i) {
		//cout << i + 1 << ":\t";
		vector<int> temp = combiResultVec[i];
		for (int j = 0; j < temp.size(); ++j) {
			//cout << temp[j] << " ";
		}
		//cout << endl;
	}

	int currSum = 0;
	int sum = 0;
	for (int i = 0; i < combiResultVec.size(); ++i) {
		vector<int> temp = combiResultVec[i];
		currSum = 0;
		for (int j = 0; j < temp.size(); ++j) {
			int countNum = std::count(v.begin(), v.end(), temp[j]);
			//cout << countNum << endl;
			currSum += temp[j] * countNum;
		}
		if (currSum > sum)
			sum = currSum;
	}

	cout << sum << endl;
}



/*
���ϲ��
AC��
*/
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<memory>
#include<cstring>
using namespace std;
const int maxn = 1010;
long long  a[maxn], b[maxn], c[maxn];
long long  dp[maxn][maxn], Max;
int main()
{
	long long  n, i, j, k, m, cnt = 0;
	scanf("%lld%lld", &n, &m);
	for (i = 1; i <= n; i++) scanf("%lld", &a[i]);
	sort(a + 1, a + n + 1);
	for (i = 1; i <= n; i++){
		if (a[i] != a[i - 1]) {
			b[++cnt] = a[i];
			c[cnt] = 1;
		}
		else  c[cnt]++;
	}
	memset(dp, -1, sizeof(dp));
	for (i = 0; i <= cnt; i++) dp[i][0] = 0;
	dp[1][1] = b[1] * c[1];
	Max = dp[1][1];
	for (i = 2; i <= cnt; i++)
		for (j = 1; j <= m; j++){
			dp[i][j] = dp[i - 1][j];//���õ�i��
			if (b[i] - b[i - 1] > 1) 
				dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + b[i] * c[i]);//Ҫ��i����ǰһ��ҲҪ
			else
				dp[i][j] = max(dp[i][j], dp[i - 2][j - 1] + b[i] * c[i]);//Ҫ��i������ǰһ����Ҫ
			Max = max(Max, dp[i][j]);
		}
	printf("%lld\n", Max);
	return 0;
}