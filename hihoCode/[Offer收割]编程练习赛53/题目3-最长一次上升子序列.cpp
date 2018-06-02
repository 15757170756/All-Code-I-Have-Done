/*
题目3 : 最长一次上升子序列
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定一个由N个元素组成的序列： A1, A2, ... AN，
请你找出其中最长的子序列B1, B2, ... BM满足其中至多有一次上升，
即只有一次Bi+1 - Bi > 0。

输入
第一行包含一个整数N。

第二行包含N个两辆不同的整数，A1, A2, ... AN。

对于30%的数据，1 <= N <= 1000

对于100%的数据，1 <= N <= 100000 , 1 <= Ai <= 100000

输出
最长的满足条件的序列的长度

样例输入
5
3 5 4 1 2
样例输出
4
*/



#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
int arr[maxn], pre[maxn], suf[maxn], rc[maxn], p, n;
int main(){
	//freopen("../input.txt", "r", stdin);
	cin >> n;
	memset(pre, 0, sizeof(pre)); memset(suf, 0, sizeof(suf));
	for (int i = 0; i < n; i++) cin >> arr[i];
	p = 0, memset(rc, 0x3f, sizeof(rc));
	for (int i = 0; i < n; i++) {
		if (arr[i] <= rc[p]) rc[++p] = arr[i], pre[i] = p;
		else {
			int l = 0, r = p;
			while (r - l > 1){
				int mm = (l + r) / 2;
				if (rc[mm] > arr[i]) l = mm;
				else r = mm;
			}
			if (rc[l] < arr[i]) rc[l] = arr[i]; else rc[r] = arr[i];
			pre[i] = p;
		}
	}
	p = 0, memset(rc, 0, sizeof(rc));
	for (int i = n - 1; i >= 0; i--) {
		if (arr[i] > rc[p]) rc[++p] = arr[i], suf[i] = p;
		else {
			int l = 0, r = p;
			while (r - l > 1){
				int mm = (l + r) / 2;
				if (rc[mm] < arr[i]) l = mm;
				else r = mm;
			}
			if (rc[l] > arr[i]) rc[l] = arr[i]; else rc[r] = arr[i];
			suf[i] = p;
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++) ans = max(ans, pre[i] + suf[i + 1]);
	cout << ans << endl;
	return 0;
}
















#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1e5 + 10;
int a[maxn], b[maxn], c[maxn], d[maxn];

int lowbit(int x){
	return x & (-x);
}
void modify(int * A, int x, int v){
	while (x < maxn) A[x] = max(A[x], v), x += lowbit(x);
}
int query(int * A, int x){
	int ret = 0;
	while (x) ret = max(ret, A[x]), x -= lowbit(x);
	return ret;
}

int main(){
	int N;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", a + i);
	for (int i = 1; i <= N; i++){
		c[i] = query(b, 100001 - a[i]) + 1;
		modify(b, 100001 - a[i], c[i]);
	}
	memset(b, 0, sizeof(b));
	for (int i = N; i >= 1; i--){
		d[i] = query(b, a[i]) + 1;
		modify(b, a[i], d[i]);
	}
	int M = 0, ans = 1;
	for (int i = 2; i <= N; i++){
		M = max(M, c[i - 1]);
		ans = max(ans, M + d[i]);
	}
	printf("%d\n", ans);
	return 0;
}
