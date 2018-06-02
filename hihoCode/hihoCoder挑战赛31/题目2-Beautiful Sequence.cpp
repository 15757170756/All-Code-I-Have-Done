/*
题目2 : Beautiful Sequence
时间限制:11000ms
单点时限:1000ms
内存限制:256MB
描述
对于一个正整数列a[1], ... , a[n] (n ≥ 3)，如果对于所有2 ≤ i ≤ n - 1，都有a[i-1] + a[i+1] ≥ 2 × a[i]，则称这个数列是美丽的。

现在有一个正整数列b[1], ..., b[n]，请计算：将b数列均匀随机打乱之后，得到的数列是美丽的概率P。

你只需要输出（P × (n!)）mod 1000000007即可。（显然P × (n!)一定是个整数）

输入
第一行一个整数n。 (3 ≤ n ≤ 60)
接下来n行，每行一个整数b[i]。 (1 ≤ b[i] ≤ 1000000000)

输出
输出（P × (n!)）mod 1000000007。

样例输入
4
1
2
1
3
样例输出
8
*/



#include<bits/stdc++.h>
#define ll long long
#define mod 1000000007
#define N 69
#define ad(x,y) (x=(x+(y))%mod)
using namespace std;

int n, last, now, a[N], b[N], cnt, c[N], dp[2][N][N][N][2], num[N];
void ins(int t1, int t2, int t3, int t4, int x, int y){
	if (num[t1] - num[x] <= num[t2] - num[t1])
		ad(dp[now][t1][t3][t4][0], y);
	if (num[x] - num[t4] >= num[t4] - num[t3])
		ad(dp[now][t1][t2][t4][1], y);
}
int main(){
	scanf("%d", &n);
	int i;
	for (i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	for (i = 1; i <= n; i++){
		if (a[i] != a[i - 1] || i == 1) num[++cnt] = a[i];
		b[i] = cnt; c[cnt]++;
	}
	int x = 1, j, t1, t2, t3;
	for (i = 1; i <= c[1]; i++) x = (ll)x*i%mod;
	dp[0][1][1][1][0] = x;
	now = 0;
	//cout<<cnt<<endl;
	//for (i=1; i<=cnt; i++) cout<<i<<' '<<num[i]<<endl;
	for (i = c[1] + 1; i <= n; i++){
		last = now; now ^= 1;
		memset(dp[now], 0, sizeof(dp[now]));
		for (t1 = 1; t1 <= cnt; t1++)
			for (t2 = 1; t2 <= cnt; t2++)
				for (t3 = 1; t3 <= cnt; t3++)
					for (j = 0; j < 2; j++) if (dp[last][t1][t2][t3][j]){
						if (!j)
							ins(b[i - 1], t1, t2, t3, b[i], dp[last][t1][t2][t3][j]);
						else
							ins(t1, t2, t3, b[i - 1], b[i], dp[last][t1][t2][t3][j]);
					}
	}
	int ans = 0;
	for (t1 = 1; t1 <= cnt; t1++)
		for (t2 = 1; t2 <= cnt; t2++)
			for (t3 = 1; t3 <= cnt; t3++)
				for (i = 0; i < 2; i++) ad(ans, dp[now][t1][t2][t3][i]);
	printf("%d\n", ans);
	return 0;
}


















#include<bits/stdc++.h>
#define sqr(x) ((x)*(x))
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define ld long double
#define vi vector<int>
#define HEAP(...) priority_queue<__VA_ARGS__ >
#define heap(...) priority_queue<__VA_ARGS__,vector<__VA_ARGS__ >,greater<__VA_ARGS__ > > 
#define pii pair<int,int> 
#define pb push_back
#define mp make_pair
#define debuge cerr<<"isok"<<endl
#define debug(x) cerr<<#x<<"="<<x<<endl
#define dprintf(...) fprintf(stderr,__VA_ARGS__)
#define SS second
#define FF first
#define ls (k<<1)
#define rs (k<<1|1)
#define clr(a,x) memset(a,x,sizeof(a))
#define cpy(a,x) memcpy(a,x,sizeof(a))
#define file(x) freopen(x".in","r",stdin),freopen(x".out","w",stdout)
#define SZ(x) ((int)x.size())
using namespace std;
template<class T> inline void gmin(T &x, const T &y){ if (x > y) x = y; }
template<class T> inline void gmax(T &x, const T &y){ if (x < y) x = y; }
const int BufferSize = 1 << 16;
char buffer[BufferSize], *Bufferhead, *Buffertail;
bool Terminal;
inline char Getchar(){
	if (Bufferhead == Buffertail){
		int l = fread(buffer, 1, BufferSize, stdin);
		if (!l){ Terminal = 1; return 0; }
		Buffertail = (Bufferhead = buffer) + l;
	}
	return *Bufferhead++;
}
template<class T>inline bool read(T &x){
	x = 0; char c = Getchar(), rev = 0;
	while (c<'0' || c>'9'){ c = Getchar(); rev |= c == '-'; if (Terminal)return 0; }
	while (c >= '0'&&c <= '9') x = x * 10 + c - '0', c = Getchar();
	if (c == '.'){
		c = Getchar(); double t = 0.1;
		while (c >= '0'&&c <= '9') x = x + (c - '0')*t, c = Getchar(), t = t / 10;
	}
	x = rev ? -x : x;
	return 1;
}
template<class T1, class T2> inline bool read(T1 &x, T2 &y){ return read(x)&read(y); }
template<class T1, class T2, class T3> inline bool read(T1 &x, T2 &y, T3 &z){ return read(x)&read(y)&read(z); }
template<class T1, class T2, class T3, class T4> inline bool read(T1 &x, T2 &y, T3 &z, T4 &w){ return read(x)&read(y)&read(z)&read(w); }
inline bool reads(char *x){
	char c = Getchar();
	while (c < 33 || c>126){ c = Getchar(); if (Terminal)return 0; }
	while (c >= 33 && c <= 126) (*x++) = c, c = Getchar();
	*x = 0; return 1;
}
template<class T>inline void print(T x, const char c = '\n'){
	if (!x){ putchar('0'); putchar(c); return; }
	if (x < 0) putchar('-'), x = -x;
	int m = 0, a[20];
	while (x) a[m++] = x % 10, x /= 10;
	while (m--) putchar(a[m] + '0');
	putchar(c);
}
//--------------------------------head---------------------------------------------

const int inf = 0x3f3f3f3f;
const int N = 65, M = 100005, mod = 1e9 + 7;
template<class T, class S> inline void ch(T &x, const S y){ x = (x + y) % mod; }
inline int exp(int x, int y, const int mod = ::mod){
	int ans = 1;
	while (y){
		if (y & 1) ans = (ll)ans*x%mod;
		x = (ll)x*x%mod; y >>= 1;
	}return ans;
}

int n, cnt, a[N];
int ans, dp[N][N][N][N];

int main(){
#ifdef rqgao2014
	freopen("input.txt", "r", stdin);
#endif
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1); a[0] = a[1];
	for (int i = 1; i <= n; i++) if (a[i] == a[1]) cnt++;
	dp[cnt - 1][cnt][cnt - 1][cnt] = 1;
	for (int i = 0; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			for (int l = 0; l <= n; l++)
				for (int r = l + 1; r <= n; r++){
					int tmp = dp[i][j][l][r];
					if (!tmp) continue;
					int nex = max(max(i, j), max(l, r)) + 1;
					if (nex > n){
						ch(ans, tmp);
						continue;
					}
					if (a[nex] - a[j] >= a[j] - a[i]) ch(dp[j][nex][l][r], tmp);
					if (a[nex] - a[r] >= a[r] - a[l]) ch(dp[i][j][r][nex], tmp);
				}
	for (int i = 1; i <= cnt; i++) ans = (ll)ans*i%mod;
	printf("%d\n", ans);
	return 0;
}













#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <sstream>
#include <stack>
#include <iomanip>
using namespace std;
#define pb push_back
#define mp make_pair
typedef pair<int, int> pii;
typedef long long ll;
typedef double ld;
typedef vector<int> vi;
#define fi first
#define se second
#define fe first
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
#define Edg int M=0,fst[SZ],vb[SZ],nxt[SZ];void ad_de(int a,int b){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;}void adde(int a,int b){ad_de(a,b);ad_de(b,a);}
#define Edgc int M=0,fst[SZ],vb[SZ],nxt[SZ],vc[SZ];void ad_de(int a,int b,int c){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;vc[M]=c;}void adde(int a,int b,int c){ad_de(a,b,c);ad_de(b,a,c);}
#define es(x,e) (int e=fst[x];e;e=nxt[e])
#define esb(x,e,b) (int e=fst[x],b=vb[e];e;e=nxt[e],b=vb[e])
#define VIZ {printf("digraph G{\n"); for(int i=1;i<=n;i++) for es(i,e) printf("%d->%d;\n",i,vb[e]); puts("}");}
#define VIZ2 {printf("graph G{\n"); for(int i=1;i<=n;i++) for es(i,e) if(vb[e]>=i)printf("%d--%d;\n",i,vb[e]); puts("}");}
#define SZ 666666
int n, b[SZ];
map<int, int> cc;
int f[63][63][63][63][2];
const int MOD = 1e9 + 7;
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", b + i), ++cc[b[i]];
	sort(b + 1, b + 1 + n);
	f[1][1][1][1][0] = 1;
	for (int i = 2; i <= n; ++i)
	{
		if (b[i] == b[1])
		{
			memcpy(f[i], f[i - 1], sizeof f[0]);
			continue;
		}
		for (int j = 1; j <= n; ++j)
		{
			for (int k = 1; k <= n; ++k)
			{
				for (int l = 1; l <= n; ++l)
				{
					for (int r = 0; r < 2; ++r)
					{
						if (!f[i - 1][j][k][l][r])
							continue;
						int x = f[i - 1][j][k][l][r];
						int la, lb, rb, ra;
						if (!r)
						{
							la = i - 1; lb = j; rb = k; ra = l;
						}
						else
						{
							la = j; lb = k; rb = l; ra = i - 1;
						}
						if (b[la] - b[i] <= b[lb] - b[la])
							(f[i][la][rb][ra][0] += x) %= MOD;
						if (b[ra] - b[rb] <= b[i] - b[ra])
							(f[i][la][lb][ra][1] += x) %= MOD;
					}
				}
			}
		}
	}
	int ans = 0;
	for (int j = 1; j <= n; ++j)
	{
		for (int k = 1; k <= n; ++k)
		{
			for (int l = 1; l <= n; ++l)
			{
				for (int r = 0; r < 2; ++r)
					(ans += f[n][j][k][l][r]) %= MOD;
			}
		}
	}
	int t = cc[b[1]];
	for (int i = 1; i <= t; ++i) ans = (ll)ans*i%MOD;
	ans = (ans%MOD + MOD) % MOD;
	printf("%d\n", ans);
}
