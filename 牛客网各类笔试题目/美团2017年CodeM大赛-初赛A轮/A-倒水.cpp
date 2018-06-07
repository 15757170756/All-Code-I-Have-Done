/*
链接：https://www.nowcoder.com/acm/contest/6/A
来源：牛客网

倒水
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
有一个大水缸，里面水的温度为T单位，体积为C升。另有n杯水（假设每个杯子的容量是无限的），每杯水的温度为t[i]单位，体积为c[i]升。
现在要把大水缸的水倒入n杯水中，使得n杯水的温度相同，请问这可能吗？并求出可行的最高温度，保留4位小数。
注意：一杯温度为t1单位、体积为c1升的水与另一杯温度为t2单位、体积为c2升的水混合后，温度变为(t1*c1+t2*c2)/(c1+c2)，体积变为c1+c2。
输入描述:
第一行一个整数n, 1 ≤ n ≤ 10^5
第二行两个整数T，C,其中0 ≤ T ≤ 10^4, 0 ≤ C ≤ 10^9
接下来n行每行两个整数t[i]，c[i]
0 ≤ t[i], c[i] ≤ 10^4
输出描述:
如果非法，输出“Impossible”（不带引号)否则第一行输出“Possible"（不带引号），第二行输出一个保留4位小数的实数表示答案。

样例解释：往第二杯水中倒0.5升水
往第三杯水中到1升水
三杯水的温度都变成了20
示例1
输入
复制
3
10 2
20 1
25 1
30 1
输出
复制
Possible
20.0000
*/

/*
作者：张晴川 loj.ac
链接：https://www.nowcoder.com/discuss/28582
来源：牛客网

倒水
大致分三种情况讨论:

T 大于所有 ti:由于要求温度最大，当然是把所有水都倒完。
T 小于等于所有 ti:因为倒水只会把水的温度往 T 靠拢，所以找一个最小的 ti，把其他所
有 tj 都倒水变成 ti。
存在 ti < T 且存在 tj > T:显然无解。
代码:
*/

作者：张晴川 loj.ac
链接：https://www.nowcoder.com/discuss/28582
来源：牛客网

#include<bits/stdc++.h>
#define int64 long long
#define sqr(x) (x)*(x)
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define rep(i,x,y) for(int i=(x);i<=(y);++i)
#define VI vector<int>
#define VI64 vector<int64>
#define VS vector<string>
#define PII pair<int,int>
#define PDD pair<double,double>
#define VPII vector< PII >
#define SZ(x) ((int)(x).size())
#define N 120000
using namespace std;
int n,t[N],c[N];
int T,C;
void P(double x){
    printf("Possible\n");
    printf("%.4lf\n",x);
    exit(0);
}
void fail(){
    printf("Impossible\n");
    exit(0);
}
int main(int argv,char **argc){
freopen(argc[1],"r",stdin);
freopen(argc[2],"w",stdout);
    scanf("%d",&n);
    scanf("%d%d",&T,&C);
    cerr<<C<<endl;
    bool f1=0,f2=0;
    rep(i,1,n){
        scanf("%d%d",&t[i],&c[i]);
        if(t[i]<T)f1=1;
        if(t[i]>T)f2=1;
    }
    if(f1 && f2)fail();
    if(!f1 && !f2)P(T);
    if(f1){
        T*=-1;
        rep(i,1,n)t[i]*=-1;
    }
    int minnT=1e9;
    int64 cc=0;
    rep(i,1,n)minnT=min(minnT,t[i]);
    if(minnT==T)fail();
    rep(i,1,n)cc+=(minnT*c[i]-c[i]*t[i]);
    if(T-minnT>0 && cc>(int64)C*(T-minnT))fail();
    if(T-minnT<0 && cc<(int64)C*(T-minnT))fail();
    cerr<<"lucky"<<endl;
    if(f1){
        double f1=0,f2=0;
        f1=(double)T*C;
        f2=C;
        rep(i,1,n)f1+=t[i]*c[i],f2+=c[i];
        P(-f1/f2);
    }else P(minnT*(f1?-1:1));
    return 0;
}
