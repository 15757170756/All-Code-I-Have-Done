/*
[编程|1000分] 分数
时间限制：C/C++ 1秒，其他语言 2秒
空间限制：C/C++ 262144K，其他语言 524288K
题目描述
小胖参加了人生中最重要的比赛——MedoC资格赛。MedoC的资格赛由m轮构成，
使用常见的“加权标准分”的规则。每位选手需要参加所有的m轮的比赛。
在一轮中，能取得的分数为自己的成绩除掉最高分的成绩。
每个选手的总分为每一轮获得的分数乘上这一轮比赛占得比重。
如果在某一轮比赛中所有人获得了零分，那么所有选手在这一轮获得的分数都为0分。
比如说，资格赛一共3轮，三轮的权重分别为30%, 30%, 40%。
在第一轮中，小胖获得了300分，最高分也为300分。
在第二轮中，小胖获得了0分，最高分也为0分。
在第三轮中，小胖获得了150分，最高分为300分，
那么小胖的总分为(300/300)*30%+0*30%+(150/300)*40%=0.5。
一共有n位选手参加了比赛，其中成绩最高的k位选手能够晋级到初赛。
如果有多人在分数线上同分，那么系统会随机在这些同分的人中选取，选满k个晋级为止。
小胖现在知道了每个选手每场比赛的成绩，但是由于他的疏忽，
其中的某个人某场比赛的成绩消失了。
所以更多人出线的情况变得未知起来。
现在只知道成绩一定是0到C之间的一个整数（包含0和C）。
小胖想知道对于每个人的出线情况是怎么样的，
也就是一定能出线，一定不能出线还是有可能出线。
输入描述:
第一行四个正整数n,m,k,C (m <= 6, k <= n <= 500, C <= 500)。
接下来一行m个整数w1, w2, ..., wm，表示每场比赛的权重，
第i场比赛的权重为wi/(w1+w2+...+wm)，
保证wi >= 0且1 <= w1 + w2 + ... + wm <= 1000。
接下来n行每行m个整数，第i个整数表示这个选手在第i场比赛中获得的成绩。
如果这个数字为-1表示这个数据丢失，保证恰好有一个-1。
输出描述:
n行每行输出一个1到3之间的整数。1表示一定出线，2表示一定不出线，3表示可能出线。
示例1
输入
4 2 2 100
1 1
100 99
70 70
40 -1
100 39
输出
1
3
3
2
*/




/*
Score：
Idea：
这是一道考验参赛者是否细心的题。 我们只要枚举丢失的那个成绩的值， 然后计算出
每个人的成绩， 按照题意看一下是否有可能入选即可。 需要注意的是这道题对于精度的
要求较高。
时间复杂度为 O(nmC + nClogn)
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1000000007;
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head

typedef unsigned long long score;

const int N=510;
int n,m,k,c,w[N],sco[N][10],sx,sy,ms[10],c1[N],c2[N];
score wt[N],s[N],t[N];

int main() {
	scanf("%d%d%d%d",&n,&m,&k,&c);
	rep(i,0,m) scanf("%d",w+i);
	rep(i,0,n) rep(j,0,m) {
		scanf("%d",&sco[i][j]);
		if (sco[i][j]==-1) { sx=i; sy=j; }
	}
	rep(x,0,c+1) {
		sco[sx][sy]=x;
		rep(j,0,m) {
			ms[j]=0;
			rep(i,0,n) ms[j]=max(ms[j],sco[i][j]);
		}
		rep(j,0,m) {
			wt[j]=w[j];
			if (ms[j]==0) { wt[j]=0; continue; }
			rep(k,0,m) if (j!=k&&ms[k]!=0) wt[j]*=ms[k];
		}
		rep(i,0,n) {
			s[i]=0;
			rep(j,0,m) s[i]+=wt[j]*sco[i][j];
			t[i]=s[i];
		}
//		puts("ff");
		nth_element(s,s+n-k,s+n);
//		puts("gg");
		rep(i,0,n) {
			if (t[i]>=s[n-k]) c1[i]++;
			if (t[i]<=s[n-k]) c2[i]++;
		}
	}
	rep(i,0,n) if (c2[i]==0) puts("1"); else if (c1[i]==0) puts("2"); else puts("3");
}