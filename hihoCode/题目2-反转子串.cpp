/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定一个只包含括号和小写字母的字符串S，例如S="a(bc(de)fg)hijk"。

其中括号表示将里面的字符串翻转。(注意括号可能嵌套)

请你输出翻转之后的字符串。

输入
字符串S。

对于50%的数据，|S| ≤ 1000

对于100%的数据, |S| ≤ 5000000

输出
输出反转后的字符串(不带括号)。

样例输入
a(bc(de)fg)hijk
样例输出
agfdecbhijk
*/


#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;
const int MAXN = 6e6 + 6;

vector<int> mcmy[MAXN];
char str[MAXN];
int arr[MAXN];
int far[MAXN];
void solve(int cur, int level) {
	if (level & 1) {
		for (int i = 0; i < mcmy[cur].size(); i++) {
			if (mcmy[cur][i] > MAXN) {
				solve(mcmy[cur][i] - MAXN, level + 1);
			}
			else {
				printf("%c", mcmy[cur][i]);
			}
		}
	}
	else {
		for (int i = mcmy[cur].size() - 1; i >= 0; i--) {
			if (mcmy[cur][i] > MAXN) {
				solve(mcmy[cur][i] - MAXN, level + 1);
			}
			else {
				printf("%c", mcmy[cur][i]);
			}
		}
	}

}
int main(){
	scanf("%s", str);
	int len = strlen(str);
	fill(far, far + MAXN, -1);
	int curcmy = -1;
	int cmycnt = 0;
	int cnt = 0;
	for (int i = 0; i < len; i++) {
		if (str[i] == '(') {
			if (curcmy == -1) {
				arr[cnt++] = cmycnt + MAXN;
				curcmy = cmycnt++;
				far[curcmy] = -1;
			}
			else {
				mcmy[curcmy].push_back(cmycnt + MAXN);
				far[cmycnt] = curcmy;
				curcmy = cmycnt++;
			}
		}
		else if (str[i] == ')'){
			curcmy = far[curcmy];
		}
		else {
			if (curcmy == -1) {
				arr[cnt++] = str[i];
			}
			else {
				mcmy[curcmy].push_back(str[i]);
			}
		}
	}
	for (int i = 0; i < cnt; i++) {
		if (arr[i] < MAXN) {
			printf("%c", arr[i]);
		}
		else {
			solve(arr[i] - MAXN, 0);
		}
	}
	//printf("\n");
	return 0;
}
















/*
Thank you for your hacking.
Hope you high rating.
*/
#include <bits/stdc++.h>
using namespace std;
#define pr(x) cerr << #x << " = " << x << endl;
#define bug cerr << "bugbug" << endl;
#define ppr(x, y) printf("(%d, %d)\n", x, y);
#define mst(a,b) memset(a,b,sizeof(a))
#define clr(a) mst(a,0)
#define sqr(a) ((a)*(a))
#define PCUT puts("\n---------------")


typedef complex<double> dcomplex;
typedef long long ll;
typedef double DBL;
typedef pair<int, int> P;
typedef unsigned int uint;
const double pi = acos(-1.0);
const double eps = 1e-12;
const int MOD = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int maxn = 5e6 + 4;
const int maxm = 1e4 + 4;
inline long long rule(long long x){ return (x %= MOD) += x < 0 ? MOD : 0; }

string ans, s;
int match[maxn];
bool vis[maxn];
stack<int> v;
int main(){
	int ik, i, j, k, kase;
	ios::sync_with_stdio(false);
	cin >> s;
	mst(match, -1);
	clr(vis);
	ans.clear();
	int cnt = 0;
	for (int i = 0; i < s.size(); ++i){
		if (s[i] == '(')
			v.push(i);
		else if (s[i] == ')'){
			int x = v.top();
			v.pop();
			match[i] = x;
			match[x] = i;
		}
	}
	int cur = 0, d = 1;
	do{
		if (!isalpha(s[cur]) && !vis[cur]){
			vis[cur] = true;
			cur = match[cur];
			vis[cur] = true;
			d = -d;
			cur += d;
		}
		else if (!isalpha(s[cur])){
			cur = match[cur];
			d = -d;
			cur += d;
		}
		else{
			ans += s[cur];
			cur += d;
		}
	} while (cur != s.size());
	cout << ans << endl;
	return 0;
}
