/*
链接：https://www.nowcoder.com/acm/contest/8/E
来源：牛客网

通信
时间限制：C/C++ 5秒，其他语言10秒
空间限制：C/C++ 802144K，其他语言1604288K
64bit IO Format: %lld
题目描述 
有N个信号塔，第i个塔的位置是i，信号强度X_i(X_i保证互不相同)。 有N个人，第i个人的位置是i，一个人往左走一格要A秒，往右走一格要B秒。 这些人之间要传递信息，具体地，如果i有信息，那么i会依次做以下操作：
- 选择一个j满足1 ≤ j ≤ i，并找到一个k使得j ≤ k ≤ i并且X_k最大来保证通信。
- i, j同时向k移动，先到的会等另一个人直到两个人都到达。
- 等到i,j都到达k时，信息的传递瞬间完成，并且i,j瞬间回到原来的位置。
- 之后i会失去信息，j会获得信息。
请对每个i计算，如果初始i有信息，那么最少多少时间以后信息可以传递到1，并输出最少时间的方案数，方案数对2^32取模。 一个方案可以被描述成P_1=i,P_2,P_3,...,P_t=1，表示信息的传递是P_1->P_2->P_3-> ...->P_t。 两个方案被认为是不同的当且仅当t不同或者存在一个1 ≤ i ≤ t使得P_i不同。 特殊地，对于1，我们认为最少时间是0，方案数为1。
输入描述:
第一行三个数N,A,B。
接下来一行N个数表示X_i。
1 ≤ N ≤ 8*10^5，1 ≤ A,B ≤ 10^4
输出描述:
令f[i]表示从i出发的最小时间,g[i]表示最小时间的方案数。
输出两行，第一行f[1] xor f[2] xor f[3] xor ... xor f[n]
第二行g[1] xor g[2] xor g[3] xor g[4] xor ... xor g[n]。
f[n]请转成64位有符号整形(c++ long long)计算xor。
g[n]请转成32位无符号整形(c++ unsigned int)计算xor。
示例1
输入
复制
6 13 3
2 4 3 5 6 1
输出
复制
6
6
说明
(f[1] = 0 , g[1] = 1
f[2] = 3 , g[2] = 1
f[3] = 13, g[3] = 1
f[4] = 9 , g[4] = 2
f[5] = 12, g[5] = 4
f[6] = 13, g[6] = 1)
*/



作者：NotDeep
链接：https://www.nowcoder.com/discuss/29150
来源：牛客网

#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <vector>
#include <bitset>
#include <string>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define REP(i, x, y) for(int i = (int)x; i <= (int)y; i ++)
#define FOR(i, x, y) for(int i = (int)x; i <  (int)y; i ++)
#define PER(i, x, y) for(int i = (int)x; i >= (int)y; i --)
#define trace(x) cerr << #x << " " << x << endl;
#define dprintf(...) fprintf(stderr, __VA__ARGS__)
#define dln()        fprintf(stderr, "\n")
using namespace std;
typedef long long LL;
typedef long double db;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<PII> VPI;
const    int N = 800005;
const    int P = 1e9 + 7;
const    int inf = 1e9;
const    LL Inf = 1e15;
const     int S = 1000005;

char bf[S],*p1=bf,*p2=bf;
#define nc() (p1==p2&&(p2=(p1=bf)+fread(bf,1,S,stdin),p2==p1)?-1:*p1++)
inline int IN(){
    int x=0;char ch=nc();for(;ch<'0'||ch>'9';ch=nc());
    for(;ch<='9'&&ch>='0';x=x*10+ch-48,ch=nc());return x;
}

inline int Pow(int x, int y, int p){
    int an = 1;
    for(; y; y >>= 1, x = (LL)x * x % p) if(y & 1) an = (LL)an * x % p;
    return an;
}

void renew(int &x, int y){
    x += y;
    if(x < 0) x += P;
    else if(x >= P) x -= P;
}

void setIO(string a){
#ifndef LOCAL
    freopen((a + ".in").c_str(), "r", stdin);
    freopen((a + ".out").c_str(), "w", stdout);
#else
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
}

template<typename T> inline void chkmin(T &a, const T &b) {if(a > b) a = b;}
template<typename T> inline void chkmax(T &a, const T &b) {if(a < b) a = b;}

typedef int ones[N];
typedef unsigned int u32;

bool st;
int n, top;
LL Lcost, Rcost;
ones X, Lx, Rx, stk;

struct Info{
    LL Min;
    u32 ways;
    Info() = default;
    Info(LL a, u32 b) : Min(a), ways(b) {}
};

Info operator +(const Info &a, const Info &b) {
    return (a.Min < b.Min) ? a : ((a.Min > b.Min) ? b : Info(a.Min, a.ways + b.ways));
}

Info operator +(const Info &a, const LL &b) {
    return Info(a.Min + b, a.ways);
}

Info A[16551425], B[16551425], C[16551425], D[16551425];
Info *curA = A, *curB = B, *curC = C, *curD = D;
Info dp[N];

//dp[i] = min(j < i) dp[j] + max(Ai - Ax, Bx - Bj)
//m1, x1 max = i
//m2, x2 max = j

struct segnode{
    Info *m1, *m2, *x1, *x2;
    int xl, xr, xmd;
    void init(int l, int r){
        xl = l;
        xr = r;
        xmd = (l + r) / 2;
        m1 = curA; curA += r - l + 2;
        m2 = curB; curB += r - l + 2;
        x1 = curC; curC += r - l + 2;
        x2 = curD; curD += r - l + 2;
        REP(i, l, r) x1[i - l + 1].Min = 1LL << 60;
        REP(i, l, r) x2[i - l + 1].Min = 1LL << 60;
    }
    void work(){
        REP(i, xl, xr) m1[i - xl + 1] = dp[i];
        REP(i, xl, xr) m2[i - xl + 1] = dp[i] + (-Rcost * i);
        REP(i, xmd + 2 - xl + 1, xr - xl + 1) m1[i] = m1[i - 1] + m1[i], m2[i] = m2[i - 1] + m2[i];
        PER(i, xmd - 1 - xl + 1, 1) m1[i] = m1[i + 1] + m1[i], m2[i] = m2[i + 1] + m2[i];
    }
    Info askopt1(int l, int r){
        return m1[l - xl + 1] + m1[r - xl + 1];
    }
    Info askopt2(int l, int r){
        return m2[l - xl + 1] + m2[r - xl + 1];
    }
    void renew(){
        Info d1 = Info(1LL << 60, 0), d2 = d1;
        REP(i, xl, xmd){
            d1 = d1 + x1[i - xl + 1];
            d2 = d2 + x2[i - xl + 1];
            dp[i] = dp[i] + (d1 + (Lcost * i));
            dp[i] = dp[i] + d2;
        }
        d1 = Info(1LL << 60, 0), d2 = d1;
        PER(i, xr, xmd + 1){
            d1 = d1 + x1[i - xl + 1];
            d2 = d2 + x2[i - xl + 1];
            dp[i] = dp[i] + (d1 + (Lcost * i));
            dp[i] = dp[i] + d2;
        }
    }
    void tag1(int l, int r, Info v){
//        assert(xl <= l && l <= xmd && xmd < r && r <= xr);
        l = l - xl + 1;
        r = r - xl + 1;
        x1[l] = x1[l] + v;
        x1[r] = x1[r] + v;
    }
    void tag2(int l, int r, Info v){
//        assert(xl <= l && l <= xmd && xmd < r && r <= xr);
        l = l - xl + 1;
        r = r - xl + 1;
        x2[l] = x2[l] + v;
        x2[r] = x2[r] + v;
    }
} T[2100005];
int ID[N];

#define LEADZERO(x) (__builtin_clz(x) - 2)
#define HIGH_BIT(x) (30 - LEADZERO(x))
#define findv(l, r) ((ID[l]) >> HIGH_BIT(ID[l] ^ ID[r]))

Info ask1(int l, int r){
    if(l == r) return dp[l];
    int x = findv(l, r);
    return T[x].askopt1(l, r);
}

Info ask2(int l, int r){
    if(l == r) return dp[l] + (-Rcost * l);
    int x = findv(l, r);
    return T[x].askopt2(l, r);
}

void Tag1(int l, int r, Info v){
    if(l == r){
        dp[l] = dp[l] + (v + Lcost * l);
        return;
    }
    int x = findv(l, r);
    T[x].tag1(l, r, v);
}

void Tag2(int l, int r, Info v){
    if(l == r){
        dp[l] = dp[l] + v;
        return;
    }
    int x = findv(l, r);
    T[x].tag2(l, r, v);
}

int mxp[N];
void work(int x, int L, int R){
    if(L == R) return;
    int xl = L, xr = R, xmd = (L + R) / 2;
    T[x].renew();
    work(x << 1, L, xmd);
    mxp[xmd + 1] = xmd + 1;
    REP(i, xmd + 2, xr){
        mxp[i] = mxp[i - 1];
        if(X[i] > X[mxp[i]]) mxp[i] = i;
    }
    mxp[xmd] = xmd;
    PER(i, xmd - 1, xl){
        mxp[i] = mxp[i + 1];
        if(X[i] > X[mxp[i]]) mxp[i] = i;
    }
    REP(i, xmd + 1, xr){
        LL d = Lcost * (i - mxp[i]) / Rcost, pos1 = mxp[i] - d;
        int Lt = max(Lx[mxp[i]] + 1, xl);
        pos1 = max(pos1, (LL)Lt);
        if(pos1 <= xmd) dp[i] = dp[i] + (ask1(pos1, xmd) + Lcost * (i - mxp[i]));
        pos1 = min(pos1 - 1, (LL)xmd);
        if(Lt <= pos1) dp[i] = dp[i] + (ask2(Lt, pos1) + Rcost * mxp[i]);
    }
    PER(i, xmd, xl){
        int Rt = min(Rx[mxp[i]] - 1, xr);
        LL pos1 = Rcost * (mxp[i] - i) / Lcost + mxp[i];
        pos1 = min(pos1, (LL)Rt);
        if(xmd + 1 <= pos1) Tag2(xmd + 1, pos1, dp[i] + Rcost * (mxp[i] - i));
        pos1 = max(pos1 + 1, xmd + 1LL);
        if(pos1 <= Rt) Tag1(pos1, Rt, dp[i] + (-Lcost * mxp[i]));
    }
    work(x * 2 + 1, xmd + 1, R);
    T[x].work();
}

void build(int x, int L, int R){
    if(L == R){
        ID[L] = x << LEADZERO(x);
        return;
    }
    int md = (L + R) >> 1;
    build(x << 1, L, md);
    build(x * 2 + 1, md + 1, R);
    T[x].init(L, R);
}

bool en;


int main(){

    //cerr << (&en - &st) / 1048576. << endl;
    n = IN();
    Lcost = IN();
    Rcost = IN();
    REP(i, 1, n) X[i] = IN();
    REP(i, 1, n) dp[i] = Info(1LL << 60, 0);
    dp[1] = Info(0, 1);
    REP(i, 1, n) Rx[i] = n + 1;
    REP(i, 1, n){
        while(top && X[i] > X[stk[top]]){
            Rx[stk[top]] = i;
            top --;
        }
        if(top) Lx[i] = stk[top];
        stk[++top] = i;
    }
    build(1, 1, n);
    work(1, 1, n);


    LL Ans1 = 0;
    u32 Ans2 = 0;
    REP(i, 1, n) Ans1 ^= dp[i].Min;
    REP(i, 1, n) Ans2 ^= dp[i].ways;
    cout << Ans1 << endl << Ans2 << endl;
    return 0;
}
