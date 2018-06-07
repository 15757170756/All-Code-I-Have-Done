/*
链接：https://www.nowcoder.com/acm/contest/6/B
来源：牛客网

二分图染色
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 524288K，其他语言1048576K
64bit IO Format: %lld
题目描述 
给定一个完全二分图，图的左右两边的顶点数目相同。我们要给图中的每条边染成红色、蓝色、或者绿色，并使得任意两条红边不共享端点、同时任意两条蓝边也不共享端点。
计算所有满足条件的染色的方案数，并对10^9+7取模。
(ps：本题数据量与实际比赛中数据量相比，少了一些)
输入描述:
二分图单边的顶点数目n(n ≤ 10^7)
输出描述:
输出一个整数,即所求的答案。
示例1
输入
复制
2
输出
复制
35
*/


#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const int N = (int) 1e7;
const int mod = (int) 1e9 + 7;
using namespace std;
long long fac[N+10], inv[N+10], a[N+10];
int n;
long long ex(int x, int y, int w) 
{
    if ((w = (w + y) % y) % x == 0)
        return w / x;
    return ((ex(y % x, x, -w) * y) + w) / x;
}
long long c(int n, int m)
 {
    return (long long) fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int main() 
{
    cin >> n;
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i-1] * (long long) i % mod;
    inv[n] = ex(fac[n], mod, 1);
    for (int i = n; i >= 1; --i)
        inv[i-1] = (long long) inv[i] * i % mod;
    a[0] = 1;
    for (int i = 1; i <= n; ++i)
        a[i] = (2LL * i * a[i - 1] % mod - ((long long) (i-1) * (i-1)) % mod * a[i - 2] % mod + mod) % mod;
    long long ans = 0;
    for (int i = 0; i <= n; ++i)
        ans = (ans + ((i & 1 ? mod - 1LL : 1LL) * c(n, i) % mod * c(n, i) % mod * fac[i] % mod * a[n-i] % mod * a[n-i] % mod)) % mod;
    cout << ans << endl;
}