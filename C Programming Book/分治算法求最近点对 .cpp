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
		if (d1 < d2) { distance = d1; a = a1; b = b1; }
		else { distance = d2; a = a2; b = b2; }

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
