/*
题目3 : 金额组合
时间限制:20000ms
单点时限:1000ms
内存限制:256MB
描述
小 Hi 手上有 n 张面值互不相同的钱币，且面值都是 2 的幂次，
现在他想知道，他可以组合出多少种小于等于 c 的正整数金额。

输入
第一行两个正整数 n , c  (1 ≤ n ≤ 50, 1 ≤ c ≤ 1018)

第二行n个互不相同的正整数，表示小Hi手上钱币的面值，
保证面值都是 2 的幂次，且不超过 1018

输出
输出一个整数表示答案

样例提示
可以拼出 1, 4, 5, 8, 9 

样例输入
3 10
4 1 8
样例输出
5
*/












#include <bits/stdc++.h>
using namespace std;
using LL = int64_t;
using LD = long double;
const LL INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    LL n, c;
    cin >> n >> c;
    vector<LL> a(n);
    for (auto& i : a) cin >> i;
    sort(a.rbegin(), a.rend());
    LL ans = 0;
    int k = 0;
    while (k < n) {
        while (k < n && a[k] > c) k++;
        if (n == k) break;
        ans += 1LL << (n - k - 1);
        c -= a[k];
        k++;
    }
    cout << ans << '\n';
}
