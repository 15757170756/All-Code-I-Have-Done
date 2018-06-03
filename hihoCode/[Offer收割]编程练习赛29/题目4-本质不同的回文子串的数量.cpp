/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定一个字符串S，请统计S的所有子串中，
有多少个本质不同的回文字符串？

注意如果两个位置不同的子串满足长度相同且对应字符也都相同，
则认为这两个子串本质上是相同的。

输入
一个只包含小写字母的字符串S。

对于30%的数据，S长度不超过100。

对于60%的数据，S长度不超过1000。

对于100%的数据，S长度不超过800000。

输出
回文子串的数量

样例输入
abbab
样例输出
5
*/

#include<bits/stdc++.h>
using namespace std;
const int mod1 = 1e9 + 7;
const int mod2 = 998244353;
using P = pair<int, int>;
using ll = long long;

set<P> se;
int len, ans;
char s[800009];
int h1[800009];
int h2[800009];
int p1[800009];
int p2[800009];
int r[800009];

void in(int i, int j){
	int ha1 = (h1[j] + mod1 - (ll)h1[i - 1] * p1[j - i + 1] % mod1) % mod1;
	int ha2 = (h2[j] + mod2 - (ll)h2[i - 1] * p2[j - i + 1] % mod2) % mod2;
	//    printf("%d %d %d %d\n",i,j,ha1,ha2);
	if (se.find(P(ha1, ha2)) == se.end()){
		se.insert(P(ha1, ha2));
		++ans;
	}
}

int main(){
	scanf("%s", s + 1);
	s[0] = 1;
	ans = 0;
	se.clear();
	len = strlen(s + 1);
	p1[0] = p2[0] = 1;
	h1[0] = h2[0] = 1;
	for (int i = 1; i <= len; ++i){
		p1[i] = (ll)p1[i - 1] * 131 % mod1;
		p2[i] = (ll)p2[i - 1] * 131 % mod2;
		h1[i] = ((ll)h1[i - 1] * 131 + s[i]) % mod1;
		h2[i] = ((ll)h2[i - 1] * 131 + s[i]) % mod2;
	}
	int x = 0, p = 0;
	for (int i = 1; i <= len; ++i){
		int j = 0;
		in(i, i);
		if (p > i)j = min(r[2 * x - i], p - i);
		while (i + j + 1 <= len&&s[i + j + 1] == s[i - j - 1]){
			++j;
			in(i, i + j);
		}
		r[i] = j;
		if (i + j > p){
			p = i + j;
			x = i;
		}
	}
	x = 0, p = 0;
	se.clear();
	for (int i = 2; i <= len; ++i){
		int j = 0;
		if (p > i)j = min(r[2 * x - i], p - i + 1);
		while (i + j <= len&&s[i + j] == s[i - j - 1]){
			in(i, i + j);
			++j;
		}
		r[i] = j;
		if (i + j - 1 > p){
			p = i + j - 1;
			x = i;
		}
	}
	printf("%d\n", ans);
	return 0;
}
