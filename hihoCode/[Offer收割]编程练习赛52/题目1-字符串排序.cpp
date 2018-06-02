/*
题目1 : 字符串排序
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
一般我们在对字符串排序时，都会按照字典序排序。当字符串只包含小写字母时，相当于按字母表"abcdefghijklmnopqrstuvwxyz"的顺序排序。

现在我们打乱字母表的顺序，得到一个26个字母的新顺序。例如"bdceafghijklmnopqrstuvwxyz"代表'b'排在'd'前，'d'在'c'前，'c'在'e'前……

给定N个字符串，请你按照新的字母顺序对它们排序。

输入
第一行包含一个整数N。(1 <= N <= 1000)

第二行包含26个字母，代表新的顺序。

以下N行每行一个字符串S。 (|S| <= 100)

输出
按新的顺序输出N个字符串，每个字符串一行。

样例输入
5
bdceafghijklmnopqrstuvwxyz
abcde
adc
cda
cad
ddc
样例输出
ddc
cda
cad
abcde
adc

*/


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>

using namespace::std;

string base;

bool cmp(string &s1, string &s2)
{
	map<int, char> mapChar;
	for (int i = 0; i < base.size(); ++i)
		mapChar.emplace(base[i], i);

	int cnt = 0;
	for (int i = 0; i < s1.size() && i < s2.size();){
		if (mapChar[s1[i]] > mapChar[s2[i]]) {
			++i;
			return mapChar[s1[i]] < mapChar[s2[i]];
		}
		else {
			return true;
		}
	}

}




int main(int argc, char* argv[])
{
	ifstream in("input.txt");

	int n;
	in >> n;
	in >> base;
	vector<string> vecStr(n);
	for (int i = 0; i < n; ++i)
		in >> vecStr[i];

	sort(vecStr.begin(), vecStr.end(), cmp);

	for (int i = 0; i < vecStr.size(); ++i) {
		cout << vecStr[i] << endl;
	}

	return 0;
}














#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>

using namespace::std;

const int MAX_N = 1e3 + 5;
int rk[30];
string str[MAX_N];
bool cmp(string x, string y)
{
	int xL = x.length(), yL = y.length();
	for (int i = 0, j = 0; i < xL && j < yL; i++, j++) {
		if (rk[x[i] - 'a'] < rk[y[j] - 'a'])
			return true;
		if (rk[x[i] - 'a'] > rk[y[j] - 'a'])
			return false;
	}
	if (yL != y.length())
		return true;
	else
		return false;
}
int main()
{
	string rule;
	int n;
	cin >> n >> rule;
	for (int i = 0; i < 26; i++) {
		rk[rule[i] - 'a'] = i;
	}
	for (int i = 0; i < n; i++) {
		cin >> str[i];
	}
	sort(str, str + n, cmp);
	for (int i = 0; i < n; i++)
		cout << str[i] << endl;
	return 0;
}



