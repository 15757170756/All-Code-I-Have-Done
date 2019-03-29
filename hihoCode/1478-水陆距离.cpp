/*
#1478 : 水陆距离
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定一个N x M的01矩阵，其中1表示陆地，0表示水域。对于每一个位置，求出它距离最近的水域的距离是多少。  

矩阵中每个位置与它上下左右相邻的格子距离为1。

输入
第一行包含两个整数，N和M。

以下N行每行M个0或者1，代表地图。

数据保证至少有1块水域。

对于30%的数据，1 <= N, M <= 100  

对于100%的数据，1 <= N, M <= 800

输出
输出N行，每行M个空格分隔的整数。每个整数表示该位置距离最近的水域的距离。

样例输入
4 4  
0110  
1111  
1111  
0110
样例输出
0 1 1 0  
1 2 2 1  
1 2 2 1  
0 1 1 0
*/


/*
《水陆距离》题目分析
本题是一道比较简单的BFS找最短路的题目。

我们可以将NxM的每一个位置看作图中的一个点；两个点如果在矩阵中上下左右相邻，我们就在这两个点之间连一条边，长度为1。

容易看出每个点最多连出4条边，整个图是一个稀疏图。

我们将所有矩阵中的0代表的点看成起始点集，这个题就变成了求其他所有点到起始点集的最短路。

由于所有边的长度都为1，所以最短路可以用BFS求出。

我们可以把起始点集中的点都先放到BFS的队列中，BFS第一次访问到某个点时经过的步数，就是这个点距离初始点集的最短距离。

总时间复杂度是O(NM)的。
*/

#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <string>
#include <stack>
#include <cmath>
#include <queue>
#include <list>
#include <set>
#include <cstring>
#include <functional>
#include <deque>
#include <cstdio>
#include <iomanip>

using namespace::std;
//freopen("input.txt", "r+", stdin);

int n, m;
const int manxn = 800 + 8;
char matrix[manxn][manxn];
int res[manxn][manxn];

int dx[] = { 0,0,-1,1 };
int dy[] = { -1,1,0,0 };

int main() 
{
	//freopen("input.txt", "r+", stdin);
	scanf("%d%d", &n, &m);
	queue<pair<int, int>> q;
	memset(res, -1, sizeof(res));
	for (int i = 0; i < n; ++i) {
		scanf("%s", matrix[i]);
		for (int j = 0; j < m; ++j) {
			if (matrix[i][j] == '0') {
				q.emplace(i, j);
				res[i][j] = 0;
			}
		}
	}
	while (!q.empty()) {
		pair<int, int> e = q.front();
		q.pop();
		for (int k = 0; k < 4; ++k) {
			int x = e.first + dx[k];
			int y = e.second + dy[k];
			if (x >= 0 && x < n && 
				y >= 0 && y < m) {
				if (res[x][y] == -1) {
					res[x][y] = res[e.first][e.second] + 1;
					q.emplace(x, y);
				}
			}
		}
	}
	for(int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			printf("%d%c", res[i][j], j == m - 1 ? '\n' : ' ');
		}

	return 0;
}

/*
结果:Accepted 
得分:100 / 100
*/















//距离变换
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <string>
#include <stack>
#include <cmath>
#include <queue>
#include <list>
#include <set>
#include <cstring>
#include <functional>
#include <deque>
#include <cstdio>
#include <iomanip>
#include <numeric>
#include <limits>
#include <climits>

using namespace::std;
//freopen("input.txt", "r+", stdin);
typedef unsigned char uchar;
int n, m;
const int maxn = 800 + 10;
char matrix[maxn][maxn];
float res[maxn][maxn];

int border = 1;

static const int DIST_SHIFT = 16;
static const int INIT_DIST0 = (INT_MAX >> 2);
#define  CV_FLT_TO_FIX(x,n)  round((x)*(1<<(n)))

static void
initTopBottom(vector<vector<int>> &temp)
{
	for (int i = 0; i < border; i++)
	{
		int* ttop = temp[i].data();
		int* tbottom = temp[temp.size() - i - 1].data();

		for (int j = 0; j < temp[0].size(); j++)
		{
			ttop[j] = INIT_DIST0;
			tbottom[j] = INIT_DIST0;
		}
	}
}

static void
distanceTransform_3x3(vector<vector<int>> &temp)
{
	const int BORDER = 1;
	int i, j;
	const int HV_DIST = CV_FLT_TO_FIX(1.0, DIST_SHIFT);
	const int DIAG_DIST = CV_FLT_TO_FIX(2.0, DIST_SHIFT);
	const float scale = 1.f / (1 << DIST_SHIFT);

	//const uchar* src = _src.ptr();
	//int* temp = _temp.ptr<int>();
	//float* dist = _dist.ptr<float>();
	//int srcstep = (int)(_src.step / sizeof(src[0]));
	int step = m + 2;
	//int dststep = (int)(_dist.step / sizeof(dist[0]));
	//Size size = _src.size();

	initTopBottom(temp);

	// forward pass
	for (i = 0; i < n; i++)
	{
		const char* s = matrix[i];
		//int* tmp = (int*)(temp[i].data() + (i + BORDER)*step) + BORDER;

		/*for (j = 0; j < BORDER; j++)
			tmp[-j - 1] = tmp[m + j] = INIT_DIST0;*/
		temp[i + 1][0] = temp[i + 1][m + 1] = INIT_DIST0;

		for (j = 0; j < m; j++)
		{
			if (s[j] == '0')
				//tmp[j] = 0;
				temp[i + 1][j + 1] = 0;
			else
			{
				//int t0 = tmp[j - step - 1] + DIAG_DIST;
				//int t = tmp[j - step] + HV_DIST;
				int t0 = temp[i][j] + DIAG_DIST;
				int t = temp[i][j + 1] + HV_DIST;
				if (t0 > t) t0 = t;
				//t = tmp[j - step + 1] + DIAG_DIST;
				t = temp[i][j + 1] + DIAG_DIST;
				if (t0 > t) t0 = t;
				//t = tmp[j - 1] + HV_DIST;
				t = temp[i + 1][j] + HV_DIST;
				if (t0 > t) t0 = t;
				//tmp[j] = t0;
				temp[i + 1][j + 1] = t0;
			}
		}
	}

	// backward pass
	for (i = n - 1; i >= 0; i--)
	{
		float* d = (float*)(res[i]);
		//int* tmp = (int*)(temp[i].data() + (i + BORDER)*step) + BORDER;

		for (j = m - 1; j >= 0; j--)
		{
			int t0 = temp[i + 1][j + 1];
			if (t0 > HV_DIST)
			{
				//int t = tmp[j + step + 1] + DIAG_DIST;
				int t = temp[i + 2][j + 2] + DIAG_DIST;
				if (t0 > t) t0 = t;
				//t = tmp[j + step] + HV_DIST;
				t = temp[i + 2][j + 1] + HV_DIST;
				if (t0 > t) t0 = t;
				//t = tmp[j + step - 1] + DIAG_DIST;
				t = temp[i + 2][j] + DIAG_DIST;
				if (t0 > t) t0 = t;
				//t = tmp[j + 1] + HV_DIST;
				t = temp[i + 1][j + 2] + HV_DIST;
				if (t0 > t) t0 = t;
				//tmp[j] = t0;
				temp[i + 1][j + 1] = t0;
			}
			d[j] = (float)(t0 * scale);
		}
	}
}

int main() 
{
	freopen("input.txt", "r+", stdin);
	memset(res, 0, sizeof(res));
	cin >> n >> m;
	vector<vector<int>> temp(n + 2 * border, 
		vector<int>(m + 2 * border));
	for (int i = 0; i < n; ++i)
		cin >> matrix[i];
	distanceTransform_3x3(temp);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cout << (int)res[i][j] << (j == m-1 ? '\n' : ' ');
		}
	}

	//vector<vector<int>> vec0(3, vector<int>(4));
	//int m0 = 0;
	//for (int i = 0; i < 3; ++i)
	//	for (int j = 0; j < 4; ++j)
	//		vec0[i][j] = m0++;
	//for (int i = 0; i < 3; ++i)
	//	for (int j = 0; j < 4; ++j)
	//		cout << vec0[i][j] << (j == 3 ?'\n':' ');
	//int *p = (int*)(vec0[0].data() + 3);
	//cout << *p << endl;
	return 0;
}


