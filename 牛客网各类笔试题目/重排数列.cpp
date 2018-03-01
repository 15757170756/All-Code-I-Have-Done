/*
时间限制：1秒

空间限制：100768K

小易有一个长度为N的正整数数列A = {A[1], A[2], A[3]..., A[N]}。
牛博士给小易出了一个难题:
对数列A进行重新排列,使数列A满足所有的A[i] * A[i + 1](1 ≤ i ≤ N - 1)都是4的倍数。
小易现在需要判断一个数列是否可以重排之后满足牛博士的要求。
输入描述:
输入的第一行为数列的个数t(1 ≤ t ≤ 10),
接下来每两行描述一个数列A,第一行为数列长度n(1 ≤ n ≤ 10^5)
第二行为n个正整数A[i](1 ≤ A[i] ≤ 10^9)

输出描述:
对于每个数列输出一行表示是否可以满足牛博士要求,如果可以输出Yes,否则输出No。

输入例子1:
2
3
1 10 100
4
1 2 3 4

输出例子1:
Yes
No
*/


#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace::std;

int main()
{
	int t;
	//ifstream inputTxt("input.txt");
	cin >> t;
	vector<string> vecStr;
	while (t) {
		int n;
		cin >> n;
		vector<int> vec(n);
		for (int& e : vec)
			cin >> e;

		int cnt = 0;
		for (int i = 0; i < n - 1; ++i) {
			for (int j = i + 1; j < n; ++j) {
				long long temp = vec[i] * vec[j];
				if (temp % 4 == 0 && j != i + 1) {
					swap(vec[i + 1], vec[j]);
					++cnt;
					break;
				}
				else if (temp % 4 == 0 && j == i + 1) {
					++cnt;
					break;
				}
			}
		}
		if (cnt == n - 1)
			vecStr.push_back("Yes");
		else
			vecStr.push_back("No");

		--t;
	}
	for (int i = 0; i < vecStr.size(); ++i)
		cout << vecStr[i] << endl;

	return 0;
}

/*
您的代码已保存
答案错误:您提交的程序没有通过所有的测试用例
case通过率为0.00%

对应输出应该为:
No No No No No Yes Yes No No Yes

你的输出为:
No No No No No Yes No No No No
但是已经有好几个case对了呀。。。
*/









//牛客网上面大神的答案，其实也满简单的，就是自己要分析呀。。。
// 寻找可以被4和不可以被2整除的数的个数
//一个不可以被4和2整除的数周围必须有2个可以被4整除的数，除了第一个
//那么对于每一个n1都必须有一个属于它的n4，如果没有n2，那第一个n1可以和第2个共有一个
//所以就是 n4>=n1||(n2==0&&n4>=n1-1)
#include<iostream>
using namespace std;
int main()
{
	int n;
	int l;
	int num;
	int n1, n4;
	while (cin >> n){
		for (int i = 0; i < n; i++){
			cin >> l;
			n1 = 0;
			n4 = 0;
			for (int j = 0; j < l; j++){
				cin >> num;
				if (num % 4 == 0)
					n4++;
				else if (num % 2 != 0)
					n1++;
			}
			if (n4 >= n1 || (n4 >= n1 - 1 && (n4 + n1) == l))
				cout << "Yes" << endl;
			else
				cout << "No" << endl;

		}
	}
	return 0;
}