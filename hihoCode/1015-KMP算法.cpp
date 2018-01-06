/*时间限制:1000ms
单点时限 : 1000ms
内存限制 : 256MB
描述
小Hi和小Ho是一对好朋友，出生在信息化社会的他们对编程产生了莫大的兴趣，
他们约定好互相帮助，在编程的学习道路上一同前进。

这一天，他们遇到了一只河蟹，于是河蟹就向小Hi和小Ho提出了那个经典的问题：
“小Hi和小Ho，你们能不能够判断一段文字（原串）里面是不是存在那么一些……特殊……的文字（模式串）？”

小Hi和小Ho仔细思考了一下，觉得只能想到很简单的做法，
但是又觉得既然河蟹先生这么说了，就肯定不会这么容易的让他们回答了，
于是他们只能说道：“抱歉，河蟹先生，我们只能想到时间复杂度为（文本长度 * 特殊文字总长度）的方法，
即对于每个模式串分开判断，然后依次枚举起始位置并检查是否能够匹配，但是这不是您想要的方法是吧？”

河蟹点了点头，说道：”看来你们的水平还有待提高，这样吧，
如果我说只有一个特殊文字，你能不能做到呢？“

小Ho这时候还有点晕晕乎乎的，但是小Hi很快开口道：
”我知道！这就是一个很经典的模式匹配问题！可以使用KMP算法进行求解！“

河蟹满意的点了点头，对小Hi说道：”既然你知道就好办了，
你去把小Ho教会，下周我有重要的任务交给你们！“

”保证完成任务！”小Hi点头道。

提示一：KMP的思路

提示二：NEXT数组的使用

提示三：如何求解NEXT数组

输入
第一行一个整数N，表示测试数据组数。

接下来的N * 2行，每两行表示一个测试数据。在每一个测试数据中，
第一行为模式串，由不超过10 ^ 4个大写字母组成，第二行为原串，由不超过10 ^ 6个大写字母组成。

其中N <= 20

输出
对于每一个测试数据，按照它们在输入中出现的顺序输出一行Ans，表示模式串在原串中出现的次数。

样例输入
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
样例输出
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
构建next数组
ababaca的next数组为：
0012302
当前字符与前面字符组合
的最长前缀与后缀匹配
*/
int* compute_prefix_function(string patten)
{
	int m = patten.size();
	int* next = new int[m];
	int k = 0;
	next[0] = k;
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