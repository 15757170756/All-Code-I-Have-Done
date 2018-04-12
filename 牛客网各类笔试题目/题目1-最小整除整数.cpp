/*
求1到n包含1和n的能整除所有1到n的最小整数
例子：
输入：3
输出：6
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mod 987654321
#define maxn 100010
bool vis[maxn];
ll Pow(int x, int n){
	ll ans = 1;
	while (n){
		if (n & 1) ans = ans*x%mod;
		x = x*x%mod;
		n >>= 1;
	}
	return ans;
}
int p[maxn], len = 0;
void init(){
	for (int i = 2; i < maxn; i++){
		if (vis[i]) continue;
		for (int j = 2 * i; j < maxn; j += i)
			vis[j] = true;
	}
	for (int i = 2; i < maxn; i++)
		if (!vis[i]) p[len++] = i;
}
int num[maxn];
int main(){
	init();
	int n, t;
	scanf("%d", &n);
	for (int i = 2; i <= n; i++){
		t = i;
		for (int j = 0; p[j] * p[j] <= t; j++){
			int cnt = 0;
			while (t%p[j] == 0){
				t /= p[j]; cnt++;
			}
			num[p[j]] = max(num[p[j]], cnt);
		}
		if (t > 1) num[t] = max(num[t], 1);
	}
	ll ans = 1;
	for (int i = 2; i < maxn; i++){
		ans = ans*Pow(i, num[i]) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
















/*
作者：Darkrai
链接：https ://www.nowcoder.com/discuss/72826
来源：牛客网

第一题：求1~N的最小公倍数。把每个数字分解质因数，
算他们每个质因数的贡献，然后乘起来。我的代码没写好（算质因数不用这么慢的）。
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 100009
int fact[maxn];
bool prime[maxn];
ll mod = 987654321;
int cal(int t, int p) {
	int cnt = 0;
	while (t % p == 0) {
		cnt++;
		t /= p;
	}
	return cnt;
}
void first() {
	memset(prime, true, sizeof(prime));
	prime[1] = false;
	for (int i = 2; i <= 100000; i++) {
		int top = sqrt(i);
		for (int j = 2; j <= top; j++) {
			if (i % j == 0) {
				prime[i] = false;
				break;
			}
		}
	}
}
void solve(int Limit) {
	first();
	for (int i = 2; i <= Limit; i++) {
		int top = sqrt(i);
		for (int j = 2; j <= top; j++) {
			if (prime[j] && i % j == 0) {
				fact[j] = max(fact[j], cal(i, j));
			}
		}
		if (prime[i])
			fact[i] = max(fact[i], 1);
	}
}
int main() {
	ll n;
	cin >> n;
	solve(n);
	ll ans = 1;
	for (ll i = 1; i <= n; i++) {
		for (ll j = 1; j <= fact[i]; j++) {
			ans = ans * i % mod;
		}
	}
	cout << ans << endl;
	return 0;
}