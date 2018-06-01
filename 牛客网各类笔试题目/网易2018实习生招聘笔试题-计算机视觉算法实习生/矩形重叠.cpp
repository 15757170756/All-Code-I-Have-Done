/*
[编程题] 矩形重叠
时间限制：1秒

空间限制：32768K

平面内有n个矩形, 第i个矩形的左下角坐标为(x1[i], y1[i]), 右上角坐标为(x2[i], y2[i])。

如果两个或者多个矩形有公共区域则认为它们是相互重叠的(不考虑边界和角落)。

请你计算出平面内重叠矩形数量最多的地方,有多少个矩形相互重叠。


输入描述:
输入包括五行。
第一行包括一个整数n(2 <= n <= 50), 表示矩形的个数。
第二行包括n个整数x1[i](-10^9 <= x1[i] <= 10^9),表示左下角的横坐标。
第三行包括n个整数y1[i](-10^9 <= y1[i] <= 10^9),表示左下角的纵坐标。
第四行包括n个整数x2[i](-10^9 <= x2[i] <= 10^9),表示右上角的横坐标。
第五行包括n个整数y2[i](-10^9 <= y2[i] <= 10^9),表示右上角的纵坐标。


输出描述:
输出一个正整数, 表示最多的地方有多少个矩形相互重叠,如果矩形都不互相重叠,输出1。

输入例子1:
2
0 90
0 90
100 200
100 200

输出例子1:
2

例子说明1:
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

const int maxn = 55;

struct Rec {
	int x1;
	int y1;
	int x2;
	int y2;
	int w;
	int h;
};

Rec recs[maxn];
int n;

bool cmp(const Rec &rec1, const Rec &rec2)
{
	if (rec1.x1 == rec2.x1)
		return rec1.y1 < rec2.y1;
	return rec1.x1 < rec2.x1;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	
	for (int i = 0; i < n; ++i)
		scanf("%d", &recs[i].x1);
	for (int i = 0; i < n; ++i)
		scanf("%d", &recs[i].y1);
	for (int i = 0; i < n; ++i)
		scanf("%d", &recs[i].x2);
	for (int i = 0; i < n; ++i)
		scanf("%d", &recs[i].y2);

	for (int i = 0; i < n; ++i) {
		int w = abs(recs[i].x1 - recs[i].x2);
		int h = abs(recs[i].y1 - recs[i].y2);
		recs[i].w = w;
		recs[i].h = h;
	}

	//sort(recs, recs + n, cmp);
	int maxNum = INT_MIN;
	for (int i = 0; i < n; ++i) {
		int cnt = 0;
		for (int j = i + 1; j < n; ++j) {
			if ((abs(recs[i].x2 - recs[j].x2) < recs[j].w
				&& abs(recs[i].y2 - recs[j].y2) < recs[j].h)
				|| (abs(recs[i].x1 - recs[j].x1) < recs[i].w)
				&& abs(recs[i].y1 - recs[j].y1) < recs[j].h)
				++cnt;
		}
		maxNum = max(maxNum, cnt);
	}
	printf("%d\n", maxNum + 1);
	return 0;
}

/*
您的代码已保存
答案错误:您提交的程序没有通过所有的测试用例
case通过率为40.00%


测试用例:
50 -328069945 67735397 -892657562 -165093050 -559275388 -754006395 325974984 -898364644 -710373715 -959457054 -823050212 -995343144 150393485 -630354810 430905060 -105617510 -624691677 664751278 -609652457 -940422577 -958960106 -826326849 -963375152 -662564893 -873545164 -91341767 -535632001 -121910469 -781317967 339852755 -497618250 -607536380 -998103775 -989417082 -892547865 -639154654 -820199079 -181568237 -889185128 -908386930 -358938084 -752694383 -857467590 534775584 -863558142 224891136 101678051 276831229 -470544526 -820128548 -350274026 -996980611 -941674927 -255473028 -463063318 -998552961 -808644220 -777764638 -209432447 -984137971 -946018977 -592229837 -603942000 -952804175 -573517413 -482002812 -44426697 -962960212 -771257730 14448147 -890718701 -512811576 -40885917 -873643171 -573285127 -929047098 -181865568 -382045777 -733028326 -898417630 -898617272 -606812936 -957158015 -938135465 -127684980 -136208193 -942458695 -739691970 -996143535 -831598725 493013037 -138975813 -927869131 -709507680 -895480314 -851611327 -972166957 -192050434 -826266975 -599903045 626787594 265814464 -81968524 -89838564 -473799417 -629415441 579574372 -784609853 -427529643 -955698432 -799102495 723751864 413113116 -255120871 706605866 -2662229 -502395907 755229439 964655389 -594051330 -794183709 -262632890 -959853203 -394799340 -715714555 25484417 -124000088 667315225 -484713675 476317446 -453151462 -521063907 -552453793 50727891 -620636125 -141324780 -500696520 926942829 393969068 -709485105 745173029 -308736087 -388870761 784568162 -839793503 941204212 222129769 428689682 -341523821 -445820498 34203574 -323760611 441336740 -232923285 794971943 -832458641 -788780545 -634463890 32643904 -717897733 -922174761 -466054021 -227095625 -935314788 -191191720 875118674 17911457 -696517456 562664317 940360753 -848481973 918876240 552601043 -224278454 209097324 -872114369 384070685 -300262213 -368726785 -648945978 676417 -338588825 -928408845 587681550 289170657 288848107 -941698662 -730701635 -689094993 569525757 871267177 856446216 -229151943 -538168170 -503038274 664970212 -924757549 995335976 -648102877 244745850 
对应输出应该为:
11 
你的输出为:
27
*/












/*
注意判断重叠矩形数量最多的地方：遍历所有可能包含的点,
看一下有多少矩形包含它
注：重叠数量最多的地方肯定是一块矩形区域

误区：A和B交，B和C交，但是A不和C交 --- B同时和A,C交, 但是重叠区域只为1
*/
//python

import sys
lines = sys.stdin.readlines()
n = int(lines[0])
x1 = list(map(int,lines[1].split()))
y1 = list(map(int,lines[2].split()))
x2 = list(map(int,lines[3].split()))
y2 = list(map(int,lines[4].split()))
# 遍历所有点的组合（包含了矩形所有角以及交点），看一下有多少矩形包含它
res = 1
for x in x1+x2:
    for y in y1+y2:
        cnt = 0
        for i in range(n):
            if x > x1[i] and y > y1[i] and x <= x2[i] and y <= y2[i]:
                cnt += 1
        res = max(res,cnt)
print(res)












//对n个点用相交关系建图，求最大团。。。

#include<bitset>
#include<stdio.h>
using namespace std;
const int maxn = 50+5;
bitset<maxn> E[maxn];
int x1[maxn],y1[maxn],x2[maxn],y2[maxn];
inline void addEdge(int x,int y){
    E[x].set(y);
    E[y].set(x);
}
bool in(int xx,int yy,int w){
    if (xx>x1[w]&&xx<x2[w]&&yy>y1[w]&&yy<y2[w])return true;
    else return false;
}
 
bool check(int x,int y){
    if (x1[x]>=x1[y]&&y1[x]>=y1[y]&&x1[x]<x2[y]&&y1[x]<y2[y]||x2[x]<=x2[y]&&y2[x]<=y2[y]&&x2[x]>x1[y]&&y2[x]>y1[y]||x1[x]>=x1[y]&&y2[x]<=y2[y]&&x1[x]<x2[y]&&y2[x]>y1[y]||x2[x]<=x2[y]&&y1[x]>=y1[y]&&x2[x]>x1[y]&&y1[x]<y2[y]||x1[x]>=x1[y]&&x2[x]<=x2[y]&&y1[x]<=y2[y]&&y2[x]>=y1[y])return true;
    else return false;
}
int n;
int ans ;
void dfs(int dep,bitset<maxn> status){
    ans = max(ans,(int)status.count());
    if (dep==n+1)return;
    if (ans>=status.count()+n-dep+1)return;
    bitset<maxn> now1=status;
    bitset<maxn> now2 = status;
    dfs(dep+1,now2);
    if (status==(status&E[dep])){
        now1.set(dep);
        dfs(dep+1,now1);
    }
}
int main(){
  //  freopen("input.in","r",stdin);
    while (scanf("%d",&n)!=EOF&&n){
        for (int i=1;i<=n;i++){
            E[i].reset();
        }
        for (int i=1;i<=n;i++){
            scanf("%d",x1+i);
        }
        for (int i=1;i<=n;i++){
            scanf("%d",y1+i);
        }
        for (int i=1;i<=n;i++){
            scanf("%d",x2+i);
        }
        for (int i=1;i<=n;i++){
            scanf("%d",y2+i);
        }
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++){
                if (i==j)continue;
                if (check(i,j))addEdge(i,j);
            }
        }
        ans=0;
        bitset<maxn> status;
        status.reset();
        dfs(1,status);
        printf("%d\n",ans);
    }
}














/*
O(n^2logn)算法。
思路是首先对所有矩形排序，按照底边坐标值升序。

考虑到若将平面按照所有矩形的的底边坐标值横向划分，
每个划分中的最大重合情况总是出现在该划分底部，且等价一维的区间重合问题。如图所示:

因此，我们每次迭代将下一个或多个底边坐标值最低的矩阵加入队列，
并将整个在当前最低坐标值之下的矩形从队列中移除，
然后用区间重合的算法计算队列中矩形在目前划分的重合数量。

*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <limits.h>
using namespace std;
// square overlap
class Square{
public:
    int left, right, up, down;
    bool operator <(const Square &x){
        return down < x.down;
    }
};
 
bool leftto(Square a, Square b){
    return a.left < b.left;
}
 
void eraselower(vector<Square> &a, int ybound){
    int deln = 0, i = 0, n = a.size();
    while(i + deln < n){
        if(a[i].up<=ybound)
            swap(a[i], a[n-(++deln)]);
        else
            ++i;
    }
    a.erase(a.end()-deln, a.end());
}
 
int main(){
    int n;
    cin>>n;
    vector<Square> sqs(n), row;
    for(int i=0; i<n; ++i)
        cin>>sqs[i].left;
    for(int i=0; i<n; ++i)
        cin>>sqs[i].down;
    for(int i=0; i<n; ++i)
        cin>>sqs[i].right;
    for(int i=0; i<n; ++i)
        cin>>sqs[i].up;
    sort(sqs.begin(), sqs.end());
    int sn = 0, curdown = 0, res = 0;
    while(sn<n){
        curdown = sqs[sn].down;
        while(sn<n && sqs[sn].down == curdown)
            row.push_back(sqs[sn++]);
        eraselower(row, curdown);
        sort(row.begin(), row.end(), leftto);
        vector<int> rights;
        for(Square x:row){
            rights.erase(rights.begin(), upper_bound(rights.begin(), rights.end(), x.left));
            rights.insert(upper_bound(rights.begin(), rights.end(), x.right), x.right);
            if(res < rights.size()) res = rights.size();
        }
    }
    cout<<res<<endl;
}












/*
注意判断重叠矩形数量最多的地方：遍历所有可能包含的点,
看一下有多少矩形包含它
注：重叠数量最多的地方肯定是一块矩形区域

误区：A和B交，B和C交，但是A不和C交 --- B同时和A,C交, 但是重叠区域只为1
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

const int maxn = 55;

struct Rec {
	int x1;
	int y1;
	int x2;
	int y2;
};

Rec recs[maxn];
int n;
int xs[2 * maxn], ys[2 * maxn];

int main()
{
	//freopen("input.txt", "r", stdin);
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		scanf("%d", &recs[i].x1);
		xs[i] = recs[i].x1;
	}
	for (int i = 0; i < n; ++i) {
		scanf("%d", &recs[i].y1);
		ys[i] = recs[i].y1;
	}
	for (int i = 0, j = n; i < n; ++i, ++j) {
		scanf("%d", &recs[i].x2);
		xs[j] = recs[i].x2;
	}
	for (int i = 0, j = n; i < n; ++i, ++j) {
		scanf("%d", &recs[i].y2);
		ys[j] = recs[i].y2;
	}
	int res = 1;
	for (int i = 0; i < 2 * n; ++i) {
		for (int j = 0; j < 2 * n; ++j) {
			int cnt = 0;
			for (int k = 0; k < n; ++k) {
				if (xs[i] > recs[k].x1
					&& ys[j] > recs[k].y1
					&& xs[i] <= recs[k].x2
					&& ys[j] <= recs[k].y2)
					++cnt;
				res = max(res, cnt);
			}
		}
	}
	
	printf("%d\n", res);

	return 0;
}
/*
您的代码已保存
答案正确:恭喜！您提交的程序通过了所有的测试用例
*/