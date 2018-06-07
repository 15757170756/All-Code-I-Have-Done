/*
链接：https://www.nowcoder.com/acm/contest/6/D
来源：牛客网

身体训练
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
美团外卖的配送员用变速跑的方式进行身体训练。
他们训练的方式是：n个人排成一列跑步，前后两人之间相隔 u 米，每个人正常速度均为 v 米/秒。
当某个配送员排在最后的时候，他需要以当时自己的最高速度往前跑，直到超过排头的人 u 米，然后降回到原始速度 v 米/秒。每个人最初的最高速度为c[i] 米/秒，每轮衰减d[i] 米/秒，也就是说，如果i是第j个跑的，那么他的速度就是c[i]-(j-1)*d[i] 米/秒。
n个人初始以随机的顺序排列，每种顺序的概率完全相等，跑完一轮（每个人都追到排头一次，序列恢复原样）的期望需要的时间是多少？
输入描述:
第一行整数n（<=1000）, 实数v(<=100) , 实数u(<=10)
第二行n个实数每个人的速度c[i](<=50000)
第三行n个实数值每个人衰减量d[i](<=10)

输入数据保证每个人的速度不会衰减到<=v
输出描述:
答案保留3位小数。
示例1
输入
复制
10 37.618 0.422
72.865 126.767 202.680 106.102 99.516 134.418 167.952 173.646 120.210 136.571
2.941 3.664 7.363 4.161 0.246 8.046 5.521 7.473 7.178 5.649
输出
复制
0.815
*/

/*
作者：张晴川 loj.ac
链接：https://www.nowcoder.com/discuss/28582
来源：牛客网

根据期望的线性性质，
枚举第 i 个人是第 j 个轮到的，每个事件的概率都是 1/n。 相当于计算:
*/

#include <cstdio>
#include <algorithm>
#include <cstring>
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define dep(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
const int N = 1005;
int n;
double v, u, c[N], d[N];
int main(){
    scanf("%d%lf%lf",&n,&v,&u);
    rep(i,1,n) scanf("%lf",c+i);
    rep(i,1,n) scanf("%lf",d+i);
    double ans = 0;
    rep(i,1,n) rep(j,1,n) ans+=1.0/(c[i]-(j-1)*d[i]-v);
    ans*=u;
    printf("%.3lf\n",ans);
}