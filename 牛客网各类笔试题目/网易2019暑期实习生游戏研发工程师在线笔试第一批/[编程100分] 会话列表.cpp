/*
[编程|100分] 会话列表
时间限制：C/C++ 1秒，其他语言 2秒
空间限制：C/C++ 32768K，其他语言 65536K
语言限定：C/C++(clang++ 3.9), Java(javac 1.8)
题目描述
小云正在参与开发一个即时聊天工具，他负责其中的会话列表部分。

会话列表为显示为一个从上到下的多行控件，其中每一行表示一个会话，
每一个会话都可以以一个唯一正整数id表示。

当用户在一个会话中发送或接收信息时，如果该会话已经在会话列表中，
则会从原来的位置移到列表的最上方；如果没有在会话列表中，则在会话列表最上方插入该会话。

小云在现在要做的工作是测试，他会先把会话列表清空等待接收信息。
当接收完大量来自不同会话的信息后，就输出当前的会话列表，以检查其中是否有bug。
输入描述:
输入的第一行为一个正整数T（T<=10），表示测试数据组数。
接下来有T组数据。每组数据的第一行为一个正整数N（1<=N<=200），
表示接收到信息的次数。第二行为N个正整数，
按时间从先到后的顺序表示接收到信息的会话id。
会话id不大于1000000000。
输出描述:
对于每一组数据，输出一行，按会话列表从上到下的顺序，输出会话id。
相邻的会话id以一个空格分隔，行末没有空格。
示例1
输入
3
5
1 2 3 4 5
6
1 100 1000 1000 100 1
7
1 6 3 3 1 8 1
输出
5 4 3 2 1
1 100 1000
1 8 3 6
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <stack>
#include <deque>

using namespace::std;

int main(int argc, char* argv[])
{
	ifstream in("input.txt");
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> vec;
		stack<int> sta;
		deque<int> deq;
		for (int i = 0; i < n; ++i) {
			bool flag = false;
			int temp;
			cin >> temp;
			vec.push_back(temp);
			deq.push_back(temp);
			for (int j = 0; j < deq.size() - 1; ++j) {
				if (temp == deq[j]) {
					flag = true;
					auto iter = deq.begin();
					deq.erase(iter + deq.size() - 1);
					if (temp != deq[0]) {
						for (int k = j; k > 0; --k)
							deq[k] = deq[k - 1];
						deq[0] = temp;
					}
					else {

					}
				}
				else {

				}
			}
			if (flag == false) {
				for (int k = deq.size() - 1; k > 0; --k)
					deq[k] = deq[k - 1];
				deq[0] = temp;
			}
		}
		int i;
		for (i = 0; i < deq.size() - 1; ++i)
			cout << deq[i] << ' ';
		cout << deq[i] << endl;
	}

	return 0;
}

/*
通过
您的代码已保存
答案正确:恭喜！您提交的程序通过了所有的测试用例
*/