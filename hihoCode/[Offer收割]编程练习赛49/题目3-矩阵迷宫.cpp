/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定一个NxN的方格矩阵迷宫，每个格子中都有一个整数Aij。
最初小Hi位于迷宫左上角的格子A11，
他每一步可以向右或向下移动，目标是移动到迷宫的出口——右下角ANN。

小Hi需要支付的代价包括路径中经过的所有格子中的整数之和，
以及改变移动方向需要支付的代价。

小Hi第一次改变方向的代价是1，第二次的代价是2，
第三次的代价是4，…… 第K次的代价是2K-1。

请你帮小Hi算出要离开迷宫代价最小的路径，并输出要支付的代价。

输入
第一行一个整数N。  (1 ≤ N ≤ 100)

以下N行每行N个整数，代表矩阵A。  (1 ≤ Aij ≤ 100)

输出
从左上角到右下角路径的最小的代价。

样例输入
3
1 3 5
1 1 2
5 1 1
样例输出
9
*/

#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 110;
const int INF = 0x3f3f3f3f;
int a[MAXN][MAXN], f[MAXN][MAXN][16][2];

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a[i][j];
    memset(f, 0x3f, sizeof(f));
    f[1][1][0][0] = f[1][1][0][1] = a[1][1];
    for (int i = 2; i <= n; i++) {
        for (int k = 0; k < 15; k++) {
            f[1][i][0][0] = a[1][i] + f[1][i - 1][0][0];
            f[i][1][0][1] = a[i][1] + f[i - 1][1][0][1];
        }
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= n; j++) {
            for (int k = 1; k < 15; k++) {
                f[i][j][k][0] = min(f[i][j - 1][k][0],
                                    f[i][j - 1][k - 1][1] + (1 << (k - 1))) +
                                a[i][j];
                f[i][j][k][1] = min(f[i - 1][j][k][1],
                                    f[i - 1][j][k - 1][0] + (1 << (k - 1))) +
                                a[i][j];
            }
        }
    }
    int ans = INF;
    for (int k = 0; k < 15; k++)
        ans = min(ans, min(f[n][n][k][0], f[n][n][k][1]));
    cout << ans << endl;
    return 0;
}