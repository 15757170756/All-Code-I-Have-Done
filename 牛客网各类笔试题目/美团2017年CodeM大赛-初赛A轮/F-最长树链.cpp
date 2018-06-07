/*
链接：https://www.nowcoder.com/acm/contest/6/F
来源：牛客网

最长树链
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
树链是指树里的一条路径。美团外卖的形象代言人袋鼠先生最近在研究一个特殊的最长树链问题。现在树中的每个点都有一个正整数值，他想在树中找出最长的树链，使得这条树链上所有对应点的值的最大公约数大于1。请求出这条树链的长度。
输入描述:
第1行：整数n（1 ≤ n ≤ 100000），表示点的个数。
第2~n行：每行两个整数x，y表示xy之间有边，数据保证给出的是一棵树。
第n+1行：n个整数，依次表示点1~n对应的权值（1 ≤ 权值 ≤ 1,000,000,000）。
输出描述:
满足最长路径的长度
示例1
输入
复制
4
1 2
1 3
2 4
6 4 5 2
输出
复制
3
*/



/*
最长树链
枚举每个约数，保留对应的边，做一次最长路径。
因为一个数的约数个数可以保证，所以复杂度符合要求。
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
int n, l, c[100001], len, value[100001], visit[100001], V[100001];
bool b[100001];
map< int, vector<int> > factor;
struct node{
  node *next;
  int where;
} a[200001], *first[100001];
inline void makelist(int x, int y) {
  a[++l].where = y;
  a[l].next = first[x];
  first[x] = &a[l];
}
pair<int, int> bfs(int init, int v, int round) {
  c[1] = init; visit[init] = 1;
  int pos = 0, will = 0;
  int k = 1, l = 1;
  for (; l <= k; ++l)
  {
    int m = c[l];
    if (visit[m] > will)
      will = visit[m], pos = m;
    for (node *x = first[m]; x; x = x->next)
      if (!(value[x->where] % v) && !visit[x->where])
      {
        visit[x->where] = visit[m] + 1;
        c[++k] = x->where;
      }
  }
  if (round == 0) 
    for (int i = 1; i <= k; i++)
      visit[c[i]] = 0;
  return make_pair(pos, will);
}
int calc(int v) {
  vector<int> idx = factor[v];
  int will = 0;
  for (int i = 0; i < idx.size(); i++)
    if (!visit[idx[i]])
    {
      will = max(will, bfs(bfs(idx[i], v, 0).first, v, 1).second);
    }
  for (int i = 0; i < idx.size(); i++)
    visit[idx[i]] = 0;
  return will;
}
     
int main() {
  len = 0;
  memset(b, false, sizeof(b));
  for (int i = 2; i <= 100000; i++)
  {
    if (!b[i])
      c[++len] = i;
    for (int j = 1; j <= len; ++j)
      if (c[j] * i > 100000)
        break;
      else
      {
        b[c[j] * i] = true;
        if (!(i % c[j]))
          break;
      }
  }
  scanf("%d", &n);
  memset(first, 0, sizeof(first)); l = 0;
  for (int i = 1; i < n; i++)
  {
    int x, y;
    scanf("%d%d", &x, &y);
    makelist(x, y);
    makelist(y, x);
  }
  factor.clear();
  for (int i = 1; i <= n; i++)
  {
    int x;
    scanf("%d", &x);
    value[i] = x;
    for (int j = 1; c[j] * c[j] <= x; ++j)
      if (!(x % c[j]))
      {
        if (factor.find(c[j]) == factor.end())
          factor[c[j]].clear();
        factor[c[j]].push_back(i);
        for (; !(x % c[j]); )
          x /= c[j];
      }
    if (x != 1)
    {
      if (factor.find(x) == factor.end())
        factor[x].clear();
      factor[x].push_back(i);
    }
  }
  int ans = 0;
  memset(visit, 0, sizeof(visit));
  memset(V, 0, sizeof(V));
  for (map< int, vector<int> >::iterator itr = factor.begin(); itr != factor.end(); ++itr)
    ans = max(ans, calc(itr->first));
  printf("%d\n", ans);
}