/*
题目3 : Good 01-Sequence
时间限制:5000ms
单点时限:1000ms
内存限制:256MB
描述
01串指的是只有0,1组成的串。对于一个01串a[1..n]，它的逆序对是指这样的(i,j)，满足1 ≤ i < j ≤ n且a[i] > a[j]。如果一个01串的逆序对数量为奇数，则称它是一个好串。例如，串1010有3个逆序对，它是一个好串；而串0100有2个逆序对，它不是一个好串。

定义这样一个函数f：对于一个01串s，如果s可以写成t1t2...tk的形式（即k个串依次连接），并且所有ti都是好串，那么定义f(s)的值为这样的最小的k；否则，定义f(s)=0。

例如：f(1010)=1，因为1010本身是一个好串。f(101010)=2，因为101010本身不是好串，但它可以拆成101和010。f(110)=0，因为它无法写成若干个好串的连接。

现在有一个长为n的01串s，它共有2n-1个非空子序列（s的子序列是指删去s的若干个数字后（或不删），剩下的数字按原来顺序形成的序列）。你需要计算这些串的f值之和，模1000000007。

例如当s=110时，你需要输出(f(1)+f(1)+f(0)+f(11)+f(10)+f(10)+f(110)) mod 1000000007。

输入
输入一行一个长度为n的01串。(1 ≤ n ≤ 100000)

输出
输出答案模1000000007。

样例输入
010010101010101010010101101010101
样例输出
421025972
*/


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
char S[SZ]; int sn;
int f[2][2][2][2][16][16];
const int MOD = 1000000007;
#define add(a,b) ((a)+=(b))%=MOD
int main()
{
	scanf("%s", S + 1);
	sn = strlen(S + 1);
	f[0][0][0][0][0][0] = 1;
	for (int i = 1; i <= sn; ++i)
	{
		int c = i & 1, b = !c;
		memset(f[c], 0, sizeof f[c]);
		for (int j = 0; j < 2; ++j)
		{
			for (int s = 0; s < 2; ++s)
			{
				for (int r = 0; r < 2; ++r)
				{
					for (int k = 0; k < 16; ++k)
					{
						for (int g = 0; g < 16; ++g)
						{
							if (!f[b][j][s][r][k][g]) continue;
							add(f[c][j][s][r][k][g],
								f[b][j][s][r][k][g]);
							{
								int jj = j, ss = s, rr = r, kk = k;
								if (S[i] == '1') ss ^= 1;
								else jj ^= 1, rr ^= ss;
								if (rr & 1) kk |= 1 << (jj + jj + ss);
								int F = 0;
								for (int p = 0; p < 4; ++p)
									if (kk&(1 << p))
									{
										int h = rr + 1 + (p % 2)*(jj + p / 2); h &= 1;
										if (h) F = 1;
									}
								int cb;
								if (!F) cb = 0;
								else cb = 1 << (jj + jj + ss);
								add(f[c][jj][ss][rr][kk][g | cb],
									f[b][j][s][r][k][g]);
							}
						}
					}
				}
			}
		}
	}
	ll ans = 0;
	for (int j = 0; j < 2; ++j)
	{
		for (int s = 0; s < 2; ++s)
		{
			for (int r = 0; r < 2; ++r)
			{
				for (int k = 0; k < 16; ++k)
				{
					for (int g = 0; g < 16; ++g)
					{
						if (!f[sn & 1][j][s][r][k][g]) continue;
						int F = 1e9;
						if (r & 1) F = min(F, 1);
						else
						{
							for (int p = 0; p < 4; ++p)
								if (k&(1 << p))
								{
									int h = 1 + (p % 2)*(j + p / 2); h &= 1;
									if (h) F = min(F, 2);
								}
						}
						for (int p = 0; p < 4; ++p)
							if (g&(1 << p))
							{
								int h = (p % 2)*(j + p / 2); h &= 1;
								if (h) F = min(F, 3);
							}
						if (F > 5e8) F = 0;
						ans += F*(ll)f[sn & 1][j][s][r][k][g] % MOD; ans %= MOD;
					}
				}
			}
		}
	}
	ans = (ans%MOD + MOD) % MOD;
	printf("%d\n", ans);
}
