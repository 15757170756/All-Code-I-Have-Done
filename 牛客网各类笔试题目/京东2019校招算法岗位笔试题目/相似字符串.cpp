相似字符串
时间限制：C/C++语言 1000MS；其他语言 3000MS
内存限制：C/C++语言 65536KB；其他语言 589824KB
题目描述：
对于仅由小写字母组成的字符串A和B，如果分别存在一个小写字母a到z的排列，使得将A中所有字母a替换为排列的第一个字母，所有字母b替换为排列的第二个字母……所有字母z替换为排列的最后一个字母之后，A和B完全相同，那么称字符串A和B相似，如abcc和xyaa。现在给定仅由小写字母组成且长度不超过105的字符串S和T，求S中有多少子串与T相似？

输入
第一行和第二行分别输入字符串S和T。

输出
输出字符串S中与T相似的子串数目。


样例输入
ababcb
xyx
样例输出
3

Hint
样例解释
S中与T相似的子串分别是aba、bab、bcb，总共3个。


#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <string>

using namespace std;

vector<int> compute_prefix_function(string &patten)
{
	int m = patten.size();
	vector<int> next(m);
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

int solve(string S, string T) 
{
	vector<int> nextT = compute_prefix_function(T);
	int len = T.size();
	int cnt = 0;
	for (int i = 0; i < S.size() - len + 1; ++i) {
		string temp = S.substr(i, len);
		vector<int> nextS = compute_prefix_function(temp);
		if (nextS == nextT)
			++cnt;
	}

	return cnt;
}
/******************************结束写代码******************************/


int main() {
	freopen("input.txt", "r", stdin);

	int res;

	string _S;
	getline(cin, _S);
	string _T;
	getline(cin, _T);

	res = solve(_S, _T);
	cout << res << endl;

	return 0;

}

通过率67%



def mapStrToNumstr(s):
    d = {}
    numstr = ""
    init = 1
    for i in s:
        if i not in d.keys():
            d[i]= str(init)
            numstr += str(init)
            init += 1
        else:
            numstr += d[i]
    return numstr
#print(mapStrToNumstr("abca"))
while True:
    try:
        s = input()
        t = input()
        lenT = len(t)
        patten = mapStrToNumstr(t)
        count = 0
        # print(patten)
        for i in range(len(s)-lenT+1):
            tmp = s[i:i+lenT]
            if mapStrToNumstr(tmp) == patten:
                count += 1
        print(count)
    except:
        break
        
AC
