/*
[编程|1000分] 下单
时间限制：C/C++ 1秒，其他语言 2秒
空间限制：C/C++ 262144K，其他语言 524288K
题目描述
美团在吃喝玩乐等很多方面都给大家提供了便利。最近又增加了一项新业务：小象生鲜。
这是新零售超市，你既可以在线下超市门店选购生鲜食品，
也可以在手机App上下单，最快30分钟就配送到家。
新店开张免不了大优惠。我们要在小象生鲜超市里采购n个物品，
每个物品价格为ai，有一些物品可以选择八折优惠（称为特价优惠）。
有m种满减优惠方式，满减优惠方式只有在所有物品都不选择特价优惠时才能使用，且最多只可以选择最多一款。
每种满减优惠描述为(bi,ci)，即满bi减ci（当消费>=bi时优惠ci）。
求要买齐这n个物品（必须一单买齐），至少需要多少钱（保留两位小数）。
输入描述:
第一行，两个整数n,m。
接下来n行，每行一个正整数ai，以及一个0/1表示是否可以选择特价优惠（1表示可以）。
接下来m行，每行两个正整数bi,ci，描述一款满减优惠。

1 <= n,m <=10
1 <= ai <= 100
1 <= ci < bi <= 1000
输出描述:
一行一个实数，表示至少需要消耗的钱数（保留恰好两位小数）。
示例1
输入
2 1
6 1
10 1
12 2
输出
12.80
示例2
输入
2 2
6 1
10 1
5 1
16 6
输出
10.00
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

using namespace std;

struct goods
{
	int price;
	int isDiscount;
};

struct discount
{
	int totalPrice;
	int subtract;
};

int main(int argc, char* argv[])
{
	//freopen("input.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	vector<goods> vecGoods(n);
	vector<discount> vecDis(m);
	int allGoodsPrice = 0;
	for (int i = 0; i < n; ++i) 
		scanf("%d%d", &vecGoods[i].price, &vecGoods[i].isDiscount);

	for (int i = 0; i < m; ++i) 
		scanf("%d%d", &vecDis[i].totalPrice, &vecDis[i].subtract);

	float allDiscountGoodsPrice = 0;
	int exceptDiscountGoodsPrict = 0;
	for (int i = 0; i < n; ++i) {
		allGoodsPrice += vecGoods[i].price;
		if (vecGoods[i].isDiscount)
			allDiscountGoodsPrice += vecGoods[i].price;
		else
			exceptDiscountGoodsPrict += vecGoods[i].price;
	}
	allDiscountGoodsPrice *= 0.8;
	float totalPrice = allDiscountGoodsPrice + exceptDiscountGoodsPrict;
	float minPrice = INT_MAX * 1.0;
	for (int i = 0; i < m; ++i) {
		float temp = allGoodsPrice;
		if (temp >= vecDis[i].totalPrice) {
			temp -= vecDis[i].subtract;
		}
		minPrice = min(minPrice, temp);
	}
	
	if (totalPrice > minPrice)
		printf("%.2f\n", minPrice);
	else
		printf("%.2f\n", totalPrice);
	return 0;
}

/*
通过
您的代码已保存
答案正确:恭喜！您提交的程序通过了所有的测试用例
*/




















/*
Order：
Idea：
这是一个在点外卖的时候经常会遇到的问题， 究竟要不要因为特价商品而放弃满减
呢？这题的思路是要选择特价商品的话， 就选所有的特价商品， 否则就走满减。 所以只
要计算一下选择八折后的最便宜的价格， 以及不选择八折的最便宜的价格， 比较一下即
可。
时间复杂度为 O(n + m)。
Solution：
https://paste.ubuntu.com/p/NrTk4pM4qx/
*/
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

void Assert(bool t){if(!t){printf("data error\n");exit(0);}}

int n,m,i,j,k,ans;
int a[15],t[15],b[15],c[15];

int calc1()
{
	int i,sum=0;
	for(i=1;i<=n;++i)
		if(t[i])
			sum+=a[i]*80;
		else 
			sum+=a[i]*100;
	return sum;
}

int calc2()
{
	int i,sum=0,ans;
	for(i=1;i<=n;++i)
		sum+=a[i];
	ans=sum;
	for(i=1;i<=m;++i)
		if(sum>=b[i])
			ans=min(ans,sum-c[i]);
	return ans*100;
}

int main()
{
	scanf("%d%d",&n,&m);
	Assert(1<=n&&n<=5);
	Assert(1<=m&&m<=5);
	for(i=1;i<=n;++i)
		scanf("%d%d",&a[i],&t[i]),Assert(1<=a[i]&&a[i]<=100&&0<=t[i]&&t[i]<=1);

	for(i=1;i<=m;++i)
		scanf("%d%d",&b[i],&c[i]),Assert(1<=c[i]&&c[i]<b[i]&&b[i]<=1000);;
	ans=min(calc1(),calc2());
	printf("%d.",ans/100);
	if(ans%100<10)
		printf("0");
	printf("%d\n",ans%100);
}