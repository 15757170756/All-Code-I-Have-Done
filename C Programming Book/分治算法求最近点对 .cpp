﻿/*
http://blog.csdn.net/hackbuteer1/article/details/7482232
*/

#include <iostream>  
#include <ctime>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

#define NO_DISTANCE 1000000

//定义二维点Point
typedef struct Point
{
	float x, y;     //二维点的横纵坐标，范围均为[-100,100]
}Point;

//用随机函数对点数组points中的二维点进行初始化
void SetPoints(Point *points, int length)
{
	srand(unsigned(time(NULL)));  //设置随机种子
	for (int i = 0; i < length; i++)
	{
		points[i].x = (rand() % 20000) / 100.0 - 100;    //调整rand(),使得横纵坐标范围为[-100,100]
		points[i].y = (rand() % 20000) / 100.0 - 100;
	}

}

//平面上任意两点对之间的距离公式计算
float Distance(Point a, Point b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

//自定义排序规则：依照结构体中的x成员变量升序排序
bool CmpX(Point a, Point b)
{
	return a.x < b.x;
}

//求出最近点对记录，并将两点记录再a、b中
float ClosestPair(Point points[], int length, Point &a, Point &b)
{
	float distance;        //记录集合points中最近两点距离 
	float d1, d2;           //记录分割后两个子集中各自最小点对距离
	int i = 0, j = 0, k = 0;       //用于控制for循环的循环变量
	Point a1, b1, a2, b2;     //保存分割后两个子集中最小点对

	if (length < 2) 
		return NO_DISTANCE;    //若子集长度小于2，定义为最大距离，表示不可达

	if (length == 2)
	{
		a = points[0];
		b = points[1];
		distance = Distance(points[0], points[1]);
	}
	else
	{
		Point *pts1 = new Point[length];     //开辟两个子集
		Point *pts2 = new Point[length];

		sort(points, points + length, CmpX);   //调用algorithm库中的sort函数对points进行排序，CmpX为自定义的排序规则
		float mid = points[(length - 1) / 2].x;  //排完序后的中间下标值，即中位数

		for (i = 0; i < length / 2; i++)
			pts1[i] = points[i];
		for (int j = 0, i = length / 2; i < length; i++)
			pts2[j++] = points[i];
		d1 = ClosestPair(pts1, length / 2, a1, b1);           //分治求解左半部分子集的最近点  
		d2 = ClosestPair(pts2, length - length / 2, a2, b2);    //分治求解右半部分子集的最近点  

		if (d1 < d2) { 
			distance = d1; 
			a = a1;
			b = b1; 
		}

		else { 
			distance = d2; 
			a = a2; 
			b = b2; 
		}

		//求解跨分割线并在δ×2δ区间内的最近点对
		Point *pts3 = new Point[length];
		for (i = 0, k = 0; i < length; i++)
			if (abs(points[i].x - mid) < distance)
				pts3[k++] = points[i];

		for (i = 0; i < k; i++)
			for (j = i + 1; j <= i + 7 && j < k; j++)    //只需与有序的领接的的7个点进行比较
			{
				if (Distance(pts3[i], pts3[j]) < distance)
				{//如果跨分割线的两点距离小于已知最小距离，则记录该距离
					distance = Distance(pts3[i], pts3[j]);
					a = pts3[i];
					b = pts3[j];
				}
			}
	}
	return distance;
}


float ClosestPairNaive(Point points[], int length, Point &a, Point &b)
{
	float minDist = DBL_MAX;
	auto euclideanDis = [](float xa, float xb, float ya, float yb)
	{
		return sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb));
	};

	for (int i = 0; i < length; ++i) {
		float x1 = points[i].x;
		float y1 = points[i].y;
		for (int j = i + 1; j < length; ++j) {
			float x2 = points[j].x;
			float y2 = points[j].y;
			float dis = euclideanDis(x1, x2, y1, y2);

			if (dis < minDist) {
				minDist = dis;
				a = points[i];
				b = points[j];
			}
		}
	}

	return minDist;
}

int main()
{
	while (1) {
		int N;      //随机生成的点对个数
		Point a, b;
		float diatance;

		cout << "请您输入二维点对个数：";
		cin >> N;
		if (N < 2)
			cout << "请输入大于等于2的点个数！！" << endl;
		else
		{
			cout << endl << "随机生成的" << N << "个二维点对如下：" << endl;
			Point *points = new Point[N];

			SetPoints(points, N);

			//for (int i = 0; i < N; i++)
			//	cout << "(" << points[i].x << "," << points[i].y << ")" << endl;

			cout << "分治算法使用时间：";
			auto start = system_clock::now();
			diatance = ClosestPair(points, N, a, b);
			auto end = system_clock::now();
			auto duration = duration_cast<microseconds>(end - start);
			cout << static_cast<double>(duration.count()) * microseconds::period::num /
				microseconds::period::den << "秒";

			//cout << "使用分治法：" << endl;
			/*cout << endl << endl << "按横坐标排序后的点对:" << endl;
			for (int i = 0; i < N; i++)
			{
			cout << "(" << points[i].x << "," << points[i].y << ")" << endl;
			}*/
			cout << endl << "最近点对为：" << "(" << a.x << "," << a.y << ")和" <<
				"(" << b.x << "," << b.y << ")" << endl << "最近点对距离为：" << diatance << endl;

			cout << endl << "暴力枚举法使用时间：";
			start = system_clock::now();
			//cout << endl << "使用暴力枚举法：" << endl;
			diatance = ClosestPairNaive(points, N, a, b);
			end = system_clock::now();
			duration = duration_cast<microseconds>(end - start);
			cout << static_cast<double>(duration.count()) * microseconds::period::num /
				microseconds::period::den << "秒";
			/*cout << endl << endl << "按横坐标排序后的点对:" << endl;
			for (int i = 0; i < N; i++)
			{
			cout << "(" << points[i].x << "," << points[i].y << ")" << endl;
			}*/
			cout << endl << "最近点对为：" << "(" << a.x << "," << a.y << ")和" <<
				"(" << b.x << "," << b.y << ")" << endl << "最近点对距离为：" << diatance << endl;
		}
	}
	system("pause");
}

























// 分治算法求最近点对
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

struct point
{
	double x, y;
}p[100005];

int a[100005];    //保存筛选的坐标点的索引

int cmpx(const point &a, const point &b)
{
	return a.x < b.x;
}
int cmpy(int &a, int &b)    //这里用的是下标索引
{
	return p[a].y < p[b].y;
}
inline double dis(point &a, point &b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
inline double min(double a, double b)
{
	return a < b ? a : b;
}
double closest(int low, int high)
{
	if (low + 1 == high)
		return dis(p[low], p[high]);
	if (low + 2 == high)
		return min(dis(p[low], p[high]), 
			min(dis(p[low], p[low + 1]), dis(p[low + 1], p[high])));
	int mid = (low + high) >> 1;
	double ans = min(closest(low, mid), closest(mid + 1, high));    //分治法进行递归求解
	int i, j, cnt = 0;
	for (i = low; i <= high; ++i)   //把x坐标在p[mid].x-ans~p[mid].x+ans范围内的点取出来 
	{
		if (p[i].x >= p[mid].x - ans && p[i].x <= p[mid].x + ans)
			a[cnt++] = i;       //保存的是下标索引
	}
	sort(a, a + cnt, cmpy);   //按y坐标进行升序排序  
	for (i = 0; i < cnt; ++i)
	{
		for (j = i + 1; j < cnt; ++j)
		{
			if (p[a[j]].y - p[a[i]].y >= ans)   //注意下标索引
				break;
			ans = min(ans, dis(p[a[i]], p[a[j]]));
		}
	}
	return ans;
}
int main(void)
{
	int i, n;
	while (scanf("%d", &n) != EOF)
	{
		if (!n)
			break;
		for (i = 0; i < n; ++i)
			scanf("%lf %lf", &p[i].x, &p[i].y);
		sort(p, p + n, cmpx);
		printf("%.2lf\n", closest(0, n - 1) / 2);
	}
	return 0;
}

/*
按照y值进行升序排列后，还可以进一步进行优化的，就是每次选取7个点就OK了，
具体原因编程之美上面有介绍的。

for (i = 0; i < cnt; ++i)
{
int k = (i + 7) > cnt ? cnt : (i + 7);    //只要选取出7个点(证明过程没看懂)
for (j = i + 1; j < k; ++j)
{
if (p[a[j]].y - p[a[i]].y >= ans)   //注意下标索引
break;
ans = min(ans, dis(p[a[i]], p[a[j]]));
}
}
*/
















/*
完整对比
*/


/*
http://blog.csdn.net/hackbuteer1/article/details/7482232
*/

#include <iostream>  
#include <ctime>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

#define NO_DISTANCE 1000000

//定义二维点Point
typedef struct Point
{
	float x, y;     //二维点的横纵坐标，范围均为[-100,100]
}Point;
Point p[1000005];

int a[1000005];    //保存筛选的坐标点的索引

//用随机函数对点数组points中的二维点进行初始化
void SetPoints(Point *points, int length)
{
	srand(unsigned(time(NULL)));  //设置随机种子
	for (int i = 0; i < length; i++)
	{
		points[i].x = (rand() % 20000) / 100.0 - 100;    //调整rand(),使得横纵坐标范围为[-100,100]
		points[i].y = (rand() % 20000) / 100.0 - 100;
	}

}

//平面上任意两点对之间的距离公式计算
float Distance(Point a, Point b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

inline double min(double a, double b)
{
	return a < b ? a : b;
}

//自定义排序规则：依照结构体中的x成员变量升序排序
bool CmpX(Point a, Point b)
{
	return a.x < b.x;
}

int cmpy(int &a, int &b)    //这里用的是下标索引
{
	return p[a].y < p[b].y;
}

//求出最近点对记录，并将两点记录再a、b中
float ClosestPair(Point points[], int length, Point &a, Point &b)
{
	float distance;        //记录集合points中最近两点距离 
	float d1, d2;           //记录分割后两个子集中各自最小点对距离
	int i = 0, j = 0, k = 0;       //用于控制for循环的循环变量
	Point a1, b1, a2, b2;     //保存分割后两个子集中最小点对

	if (length < 2)
		return NO_DISTANCE;    //若子集长度小于2，定义为最大距离，表示不可达

	if (length == 2)
	{
		a = points[0];
		b = points[1];
		distance = Distance(points[0], points[1]);
	}
	else
	{
		Point *pts1 = new Point[length];     //开辟两个子集
		Point *pts2 = new Point[length];

		sort(points, points + length, CmpX);   //调用algorithm库中的sort函数对points进行排序，CmpX为自定义的排序规则
		float mid = points[(length - 1) / 2].x;  //排完序后的中间下标值，即中位数

		for (i = 0; i < length / 2; i++)
			pts1[i] = points[i];
		for (int j = 0, i = length / 2; i < length; i++)
			pts2[j++] = points[i];
		d1 = ClosestPair(pts1, length / 2, a1, b1);           //分治求解左半部分子集的最近点  
		d2 = ClosestPair(pts2, length - length / 2, a2, b2);    //分治求解右半部分子集的最近点  

		if (d1 < d2) {
			distance = d1;
			a = a1;
			b = b1;
		}

		else {
			distance = d2;
			a = a2;
			b = b2;
		}

		//求解跨分割线并在δ×2δ区间内的最近点对
		Point *pts3 = new Point[length];
		for (i = 0, k = 0; i < length; i++)
			if (abs(points[i].x - mid) < distance)
				pts3[k++] = points[i];

		for (i = 0; i < k; i++)
			for (j = i + 1; j <= i + 7 && j < k; j++)    //只需与有序的领接的的7个点进行比较
			{
				if (Distance(pts3[i], pts3[j]) < distance)
				{//如果跨分割线的两点距离小于已知最小距离，则记录该距离
					distance = Distance(pts3[i], pts3[j]);
					a = pts3[i];
					b = pts3[j];
				}
			}
	}
	return distance;
}


double closest(int low, int high)
{
	if (low + 1 == high)
		return Distance(p[low], p[high]);
	if (low + 2 == high)
		return min(Distance(p[low], p[high]), min(Distance(p[low], p[low + 1]), Distance(p[low + 1], p[high])));
	int mid = (low + high) >> 1;
	double ans = min(closest(low, mid), closest(mid + 1, high));    //分治法进行递归求解
	int i, j, cnt = 0;
	for (i = low; i <= high; ++i)   //把x坐标在p[mid].x-ans~p[mid].x+ans范围内的点取出来 
	{
		if (p[i].x >= p[mid].x - ans && p[i].x <= p[mid].x + ans)
			a[cnt++] = i;       //保存的是下标索引
	}
	sort(a, a + cnt, cmpy);   //按y坐标进行升序排序  

#if 1
	for (i = 0; i < cnt; ++i)
	{
		int k = (i + 7) > cnt ? cnt : (i + 7);    //只要选取出7个点(证明过程没看懂)
		for (j = i + 1; j < k; ++j)
		{
			if (p[a[j]].y - p[a[i]].y >= ans)   //注意下标索引
				break;
			ans = min(ans, Distance(p[a[i]], p[a[j]]));
		}
	}
#endif

#if 0
	for (i = 0; i < cnt; ++i)
	{
		for (j = i + 1; j < cnt; ++j)
		{
			if (p[a[j]].y - p[a[i]].y >= ans)   //注意下标索引
				break;
			ans = min(ans, Distance(p[a[i]], p[a[j]]));
		}
	}
#endif
	return ans;
}


float ClosestPairNaive(Point points[], int length, Point &a, Point &b)
{
	float minDist = DBL_MAX;
	auto euclideanDis = [](float xa, float xb, float ya, float yb)
	{
		return sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb));
	};

	for (int i = 0; i < length; ++i) {
		float x1 = points[i].x;
		float y1 = points[i].y;
		for (int j = i + 1; j < length; ++j) {
			float x2 = points[j].x;
			float y2 = points[j].y;
			float Distance = euclideanDis(x1, x2, y1, y2);

			if (Distance < minDist) {
				minDist = Distance;
				a = points[i];
				b = points[j];
			}
		}
	}

	return minDist;
}

int main()
{
	while (1) {
		int N;      //随机生成的点对个数
		Point a, b;
		float diatance;

		cout << "请您输入二维点对个数：";
		cin >> N;
		if (N < 2)
			cout << "请输入大于等于2的点个数！！" << endl;
		else
		{
			cout << endl << "随机生成的" << N << "个二维点对如下：" << endl;
			Point *points = new Point[N];

			SetPoints(points, N);
			SetPoints(p, N);

			//for (int i = 0; i < N; i++)
			//	cout << "(" << points[i].x << "," << points[i].y << ")" << endl;

			cout << "分治算法1使用时间：";
			auto start = system_clock::now();
			diatance = ClosestPair(points, N, a, b);
			auto end = system_clock::now();
			auto duration = duration_cast<microseconds>(end - start);
			cout << static_cast<double>(duration.count()) * microseconds::period::num /
				microseconds::period::den << "秒";

			//cout << "使用分治法：" << endl;
			/*cout << endl << endl << "按横坐标排序后的点对:" << endl;
			for (int i = 0; i < N; i++)
			{
			cout << "(" << points[i].x << "," << points[i].y << ")" << endl;
			}*/
			cout << endl << "最近点对为：" << "(" << a.x << "," << a.y << ")和" <<
				"(" << b.x << "," << b.y << ")" << endl << "最近点对距离为：" << diatance << endl;


			cout << endl << "分治算法2使用时间：";
			start = system_clock::now();
			sort(p, p + N, CmpX);
			diatance = closest(0, N - 1);
			end = system_clock::now();
			duration = duration_cast<microseconds>(end - start);
			cout << static_cast<double>(duration.count()) * microseconds::period::num /
				microseconds::period::den << "秒";
			cout << endl << "最近点对为：" << "(" << a.x << "," << a.y << ")和" <<
				"(" << b.x << "," << b.y << ")" << endl << "最近点对距离为：" << diatance << endl;


			cout << endl << "暴力枚举法使用时间：";
			start = system_clock::now();
			//cout << endl << "使用暴力枚举法：" << endl;
			diatance = ClosestPairNaive(points, N, a, b);
			end = system_clock::now();
			duration = duration_cast<microseconds>(end - start);
			cout << static_cast<double>(duration.count()) * microseconds::period::num /
				microseconds::period::den << "秒";
			/*cout << endl << endl << "按横坐标排序后的点对:" << endl;
			for (int i = 0; i < N; i++)
			{
			cout << "(" << points[i].x << "," << points[i].y << ")" << endl;
			}*/
			cout << endl << "最近点对为：" << "(" << a.x << "," << a.y << ")和" <<
				"(" << b.x << "," << b.y << ")" << endl << "最近点对距离为：" << diatance << endl;
		}
		cout << endl << endl;
	}
	system("pause");
}


/*
请您输入二维点对个数：987

随机生成的987个二维点对如下：
分治算法1使用时间：0.007979秒
最近点对为：(-4.15,-78.65)和(-4.05,-78.7)
最近点对距离为：0.111801

分治算法2使用时间：0.001994秒
最近点对为：(-4.15,-78.65)和(-4.05,-78.7)
最近点对距离为：0.111801

暴力枚举法使用时间：0.032911秒
最近点对为：(-4.15,-78.65)和(-4.05,-78.7)
最近点对距离为：0.111801


请您输入二维点对个数：9987

随机生成的9987个二维点对如下：
分治算法1使用时间：0.099769秒
最近点对为：(13.73,-17.77)和(13.74,-17.78)
最近点对距离为：0.0141425

分治算法2使用时间：0.042884秒
最近点对为：(13.73,-17.77)和(13.74,-17.78)
最近点对距离为：0.0141425

暴力枚举法使用时间：3.45177秒
最近点对为：(13.73,-17.77)和(13.74,-17.78)
最近点对距离为：0.0141425
*/