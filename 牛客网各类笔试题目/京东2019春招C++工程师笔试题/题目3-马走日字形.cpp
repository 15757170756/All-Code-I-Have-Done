/*
象棋的马走K步之后到(X,Y)的方案数。直接递推。
*/


#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define maxn 100010
int dp[maxn][9][9];
int dir[8][2] = { { 1, 2 }, { -1, 2 }, { 1, -2 }, 
{ -1, -2 }, { 2, 1 }, { 2, -1 }, 
{ -2, 1 }, { -2, -1 } };
int main(){
	dp[0][0][0] = 1;
	int K, x, y;
	scanf("%d%d%d", &K, &x, &y);
	for (int t = 1; t <= K; t++){
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				for (int k = 0; k < 8; k++){
					int nx = i + dir[k][0];
					int ny = j + dir[k][1];
					if (nx >= 0 && ny >= 0 && nx < 9 && ny < 9)
						dp[t][i][j] = (dp[t][i][j] + dp[t - 1][nx][ny]) % mod;
				}
			}
		}
	}
	printf("%d\n", dp[K][x][y]);
	return 0;
}














作者：Darkrai
链接：https ://www.nowcoder.com/discuss/72826
来源：牛客网

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[10][10][3];
ll mod = 1e9 + 7;
int dx[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int dy[8] = { -1, -2, -2, -1, 1, 2, 2, 1 };
int check(int x, int y) {
	if (x >= 0 && x <= 8 && y >= 0 && y <= 8)
		return true;
	return false;
}
void cal(int x, int y, int state) {
	dp[x][y][state] = 0;
	for (int i = 0; i < 8; i++) {
		int tx = x + dx[i];
		int ty = y + dy[i];
		if (check(tx, ty)) {
			dp[x][y][state] = (dp[x][y][state] + dp[tx][ty][state ^ 1]) % mod;
		}
	}
}
int main() {
	int K;
	cin >> K;
	int state = 0, nowstate;
	dp[0][0][0] = 1;
	while (K--) {
		state = state ^ 1;
		for (int i = 0; i <= 8; i++) {
			for (int j = 0; j <= 8; j++) {
				cal(i, j, state);
			}
		}
	}
	int x, y;
	cin >> x >> y;
	cout << dp[x][y][state] << endl;
	return 0;
}