/*
题目描述
计算 24 点是一种扑克牌益智游戏，随机抽出 4 张扑克牌，通过加 (+) ，减 (-) ，乘 ( * ),  
除 (/) 四种运算法则计算得到整数 24 ，本问题中，扑克牌通过如下字符或者字符串表示，
其中，小写 joker 表示小王，大写 JOKER 表示大王：  

                   3 4 5 6 7 8 9 10 J Q K A 2 joker JOKER

本程序要求实现：输入 4 张牌，输出一个算式，算式的结果为 24 点。  

详细说明：  

1. 运算只考虑加减乘除运算，没有阶乘等特殊运算符号， 友情提醒，整数除法要当心 ；  
2. 牌面 2~10 对应的权值为 2~10, J 、 Q 、 K 、 A 权值分别为为 11 、 12 、 13 、 1 ；  
3. 输入 4 张牌为字符串形式，以 一个空格 隔开，首尾无空格；如果输入的 4 张牌中包含大小王，
则输出字符串“ ERROR ”，表示无法运算；  
4. 输出的算式格式为 4 张牌通过 /*+-
 四个运算符相连， 中间无空格 ， 4 张牌出现顺序任意，只要结果正确；  
5. 输出算式的运算顺序从左至右，不包含括号 ，如 1+2+3*4 的结果为 24
6. 如果存在多种算式都能计算得出 24 ，只需输出一种即可，如果无法得出 24 ，则输出“ NONE ”表示无解。

输入描述:
输入4张牌为字符串形式，以一个空格隔开，首尾无空格；

输出描述:
如果输入的4张牌中包含大小王，则输出字符串“ERROR”，表示无法运算； 
示例1
输入
A A A A
输出
NONE
*/


#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <string>
#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

char card[4][10];
int num[4];
char operatorChar[4] = { '+', '-', '*', '/' };
int ans;

bool isWork(vector<int> &vec, char ch1, char ch2, char ch3)
{
	float tempSum = 0;

	if (ch1 == '+')
		tempSum += (vec[0] + vec[1]);
	else if (ch1 == '-')
		tempSum += (vec[0] - vec[1]);
	else if (ch1 == '*')
		tempSum += (vec[0] * vec[1]);
	else if (ch1 == '/')
		tempSum += (vec[0] * 1.0 / vec[1]);

	if (ch2 == '+')
		tempSum = (tempSum + vec[2]);
	else if (ch2 == '-')
		tempSum = (tempSum - vec[2]);
	else if (ch2 == '*')
		tempSum = (tempSum * vec[2]);
	else if (ch2 == '/')
		tempSum = (tempSum / vec[2]);

	if (ch3 == '+')
		tempSum = (tempSum + vec[3]);
	else if (ch3 == '-')
		tempSum = (tempSum - vec[3]);
	else if (ch3 == '*')
		tempSum = (tempSum * vec[3]);
	else if (ch3 == '/')
		tempSum = (tempSum / vec[3]);

	if (abs(tempSum - 24) < 0.00001)
		return true;
	else
		return false;
}

void charToNum()
{
	for (int i = 0; i < 4; ++i) {
		int len = strlen(card[i]);
		if (len == 2)
			num[i] = 10;
		else if (strcmp("A", card[i]) == 0)
			num[i] = 1;
		else if (strcmp("J", card[i]) == 0)
			num[i] = 11;
		else if (strcmp("Q", card[i]) == 0)
			num[i] = 12;
		else if (strcmp("K", card[i]) == 0)
			num[i] = 13;
		else
			num[i] = stoi(card[i]);
	}
}

void NumToChar(vector<int> &vec, char ch[4][6])
{
	for (int i = 0; i < vec.size(); ++i) {
		if (vec[i] >= 2 && vec[i] <= 10) {
			sprintf(ch[i], "%d", vec[i]);
		}
		else if (vec[i] == 11)
			strcpy(ch[i], "J");
		else if (vec[i] == 12)
			strcpy(ch[i], "Q");
		else if (vec[i] == 13)
			strcpy(ch[i], "K");
		else if (vec[i] == 1)
			strcpy(ch[i], "A");
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	for (int i = 0; i < 4; ++i) 
		scanf("%s", card[i]);
	for (int i = 0; i < 4; ++i) {
		if ((strcmp("joker", card[i]) == 0) 
			|| (strcmp("JOKER", card[i]) == 0)) {
			printf("ERROR\n");
			return 0;
		}
	}
	charToNum();
	
	vector<int> vec(begin(num), end(num));
	vector<vector<int>> permutationVec;
	sort(vec.begin(), vec.end());
	do {
		permutationVec.push_back(vec);
	} while (next_permutation(vec.begin(), vec.end()));
	//for (auto e1 : permutationVec) {
	//	for (auto e2 : e1)
	//		cout << e2 << ' ';
	//	cout << endl;
	//}
	bool flag = false;
	for (int i = 0; i < permutationVec.size(); ++i) {
		vector<int> &tempVec = permutationVec[i];
		for (int k1 = 0; k1 < 4; ++k1) {
			for (int k2 = 0; k2 < 4; ++k2) {
				for (int k3 = 0; k3 < 4; ++k3) {
					char k1Char = operatorChar[k1];
					char k2Char = operatorChar[k2];
					char k3Char = operatorChar[k3];

					if (isWork(tempVec, k1Char, k2Char, k3Char)) {
						char ch[4][6];
						NumToChar(tempVec, ch);
						printf("%s%c%s%c%s%c%s\n",
							ch[0], k1Char, ch[1], k2Char, ch[2], k3Char, ch[3]);
						flag = true;
						//return 0;
					}
				}
			}
		}
	}
	if (!flag)
		printf("NONE\n");
	return 0;
}


/*
垃圾华为：

我的输出为：
A+K*2-4
K+A*2-4
K-A/2*4
K-A*4/2


不通过
您的代码已保存
答案错误:您提交的程序没有通过所有的测试用例
case通过率为0.00%

测试用例:
4 2 K A 

对应输出应该为:

K-A*4/2

你的输出为:

A+K*2-4
*/












//别人AC的代码

#include<iostream>
#include <iostream>
#include<cstdlib>
#include<cstdio>
#include<memory.h>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
#include <string>
#define mem(array)  memset((array),0,sizeof((array)))
#define Qsort(array,len,cmp) qsort(array,len,sizeof(array[0]),cmp)
#define inf 0x7fffffff
#define MAXN 10+10000
using namespace std;

string jok[2] = { "joker", "JOKER" };

int aa[4];
string str[5];

bool fun2(int a, int b, int op, int& ans)
{
	switch (op){
	case 1:
		ans = a + b;
		return true;
	case 2:
		ans = a - b;
		return true;
	case 3:
		ans = a*b;
		return true;
	case 4:
		if (a%b == 0){
			ans = a / b;
			return true;
		}
		else
			return false;
	default:
		return false;
	}
	return false;
}

bool outputOP(int op)
{
	switch (op){
	case 1:
		printf("+");
		return true;
	case 2:
		printf("-");
		return true;
	case 3:
		printf("*");
		return true;
	case 4:
		printf("/");
		return true;
	}
	return false;
}
bool outputVal(int x)
{
	switch (x){
	case 1:
		for (int i = 0; i < 4; ++i)
			if (strcmp(str[i].data(), "1") == 0){
				printf("1");
				return true;
			}
		printf("A");
		return true;
	case 11:
		printf("J");
		return true;
	case 12:
		printf("Q");
		return true;
	case 13:
		printf("K");
		return true;
	default:
		printf("%d", x);
	}
	return true;
}
bool output(int a, int b, int c, int d, int op1, int op2, int op3)
{
	outputVal(a);
	outputOP(op1);
	outputVal(b);
	outputOP(op2);
	outputVal(c);
	outputOP(op3);
	outputVal(d);
	printf("\n");

	return true;
}
bool fun(int a, int b, int c, int d)
{
	int n = 5;
	int temp;
	int ansi, ansj, ansk;
	for (int i = 1; i < n; ++i){
		if (!fun2(a, b, i, temp))
			continue;
		ansi = temp;
		for (int j = 1; j < n; ++j){
			if (!fun2(ansi, c, j, temp))
				continue;
			ansj = temp;
			for (int k = 1; k < n; ++k){
				if (!fun2(ansj, d, k, temp))
					continue;
				ansk = temp;
				if (ansk == 24){
					output(a, b, c, d, i, j, k);
					return true;
				}
			}
		}
	}
	return false;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int sign;
	while (cin >> str[0] >> str[1] >> str[2] >> str[3]){
		sign = 1;
		for (int i = 0; i < 4; ++i){
			for (int j = str[i].length(); j >= 0; --j){
				if ('a' <= str[i][j] && str[i][j] <= 'z')
					str[i][j] = str[i][j] - 'a' + 'A';
			}
			if (strcmp(str[i].data(), jok[1].data()) == 0){
				printf("ERROR\n");
				sign = 0;
				break;
			}
		}
		if (sign == 0)
			continue;
		int k = 0;
		for (int i = 0; i < 4; ++i){
			if (strcmp(str[i].data(), "J") == 0){
				aa[k++] = 11;
				continue;
			}
			if (strcmp(str[i].data(), "Q") == 0){
				aa[k++] = 12;
				continue;
			}
			if (strcmp(str[i].data(), "K") == 0){
				aa[k++] = 13;
				continue;
			}
			if (strcmp(str[i].data(), "A") == 0){
				aa[k++] = 1;
				continue;
			}
			if (strcmp(str[i].data(), "10") == 0){
				aa[k++] = 10;
				continue;
			}
			aa[k++] = str[i][0] - '0';
		}
		if (aa[0] == 4 && aa[1] == 4 && aa[2] == 2 && aa[3] == 7){
			printf("7-4*2*4\n");
			continue;
		}
		bool sign = false;
		for (int i = 0; i < 4; ++i){
			for (int j = 0; j < 4; ++j){
				if (j == i)
					continue;
				for (int k = 0; k < 4; ++k){
					if (k == i || k == j)
						continue;
					for (int l = 0; l < 4; ++l){
						if (l == i || l == j || l == k)
							continue;
						sign = fun(aa[i], aa[j], aa[k], aa[l]);
						if (sign)
							break;
					}
					if (sign)
						break;
				}
				if (sign)
					break;
			}
			if (sign)
				break;
		}

		if (!sign){
			printf("NONE\n");
		}
	}
	return 0;
}