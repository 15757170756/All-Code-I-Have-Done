/*
题目4 : 数字组合
时间限制:20000ms
单点时限:1000ms
内存限制:256MB
描述
你有 n 个数位（ 1 到 9 ），现在你需要用他们组成 k 个正整数，使得最大的数最小

输入
第一行两个正整数 n , k (1 ≤ k ≤ n ≤ 105)

第二行一个长度为 n 的数字串，表示你拥有的数位。

输出
出最大的数的最小值

样例解释
组成：17, 34, 27, 4

样例输入
7 4
4412377
样例输出
34
*/













#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>
#include <unordered_set>
#include <sstream>
#include <map>
#include <iterator>
#include <set>
#include <stack>
#include <deque>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <unordered_map>
#include <climits>

using namespace std;

const int maxn = 1e5 + 5;
int arr[maxn];
char numChar[maxn];

int main(int argc, char* argv[])
{
	freopen("input.txt", "r", stdin);
	int n, k;
	scanf("%d%d", &n, &k);
	scanf("%s", numChar);
	for (int i = 0; i < n; ++i) {
		int temp = numChar[i] - '0';
		arr[i] = temp;
	}
	sort(arr, arr + n);
	if (n == k) {
		for (int i = 0; i < n; ++i)
			printf("%d", arr[i]);
		printf("\n");
		return 0;
	}

	int bits1, bits2;
	if (n % k == 0) {
		bits1 = n / k;
		bits2 = bits1;
	}
	else {
		bits1 = n / k + 1;
		bits2 = bits1 - 1;
	}
	
	int numOfBits1, numOfBits2;
	for (numOfBits1 = 1; numOfBits1 <= n / bits1; ++numOfBits1) {
		for (numOfBits2 = 1; numOfBits2 <= n / bits2; ++numOfBits2) {
			if (numOfBits1 * bits1 + numOfBits2 * bits2 == n
				&& numOfBits1 + numOfBits2  == k)
				break;
		}
		if (numOfBits1 * bits1 + numOfBits2 * bits2 == n
			&& numOfBits1 + numOfBits2 == k)
			break;
	}
	//printf("%d %d\n", numOfBits1, numOfBits2);
	if (bits1 == bits2) {
		numOfBits1 = numOfBits2 = k;
	}
	for (int i = numOfBits1 - 1; i < numOfBits1 - 1 + bits1; ++i)
		printf("%d", arr[i]);
	printf("\n");

	return 0;
}

/*
结果:Wrong Answer
得分 : 5 / 100
*/




#include <stdio.h>

char s[100005], ans[100005];
int a[10];
int main() {
    int n, k;
    scanf("%d%d%s", &n, &k, s);
    for (int i = 0; i < n; i++) a[s[i] - '0']++;
    int w = n / k + !!(n % k);
    k = n / w;
    if (n % w) k -= w - 1 - n % w;
    int h = 0;
    for (int x = 0; x < w; x++) {
        for (int i = 1; i <= 9; i++) {
            int c = (k < a[i]?k:a[i]);
            a[i] -= c;
            k -= c;
            if (!k) {
                ans[h++] = '0' + i;
                k = c;
                break;
            }
        }
    }
    ans[h] = '\0';
    printf("%s\n", ans);
}
