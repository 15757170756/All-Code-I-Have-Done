/*
时间限制：1秒

空间限制：32768K

三维空间中有N个点，每个点可能是三种颜色的其中之一，
三种颜色分别是红绿蓝，分别用'R', 'G', 'B'表示。
现在要找出三个点，并组成一个三角形，使得这个三角形的面积最大。
但是三角形必须满足：三个点的颜色要么全部相同，要么全部不同。
输入描述:
首先输入一个正整数N三维坐标系内的点的个数.(N <= 50)

接下来N行，每一行输入 c x y z，c为'R', 'G', 'B' 
的其中一个。x，y，z是该点的坐标。(坐标均是0到999之间的整数)

输出描述:
输出一个数表示最大的三角形面积，保留5位小数。

输入例子1:
5
R 0 0 0
R 0 4 0
R 0 0 3
G 92 14 7
G 12 16 8

输出例子1:
6.00000
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <cstdio>

using namespace std;

struct Point3D
{
	int x;
	int y;
	int z;
	char color;
};

double distanceP1ToP2(Point3D p1, Point3D p2)
{
	return (sqrt((p1.x - p2.x)*(p1.x - p2.x) +
		(p1.y - p2.y)*(p1.y - p2.y) +
		(p1.z - p2.z)*(p1.z - p2.z)));
}

double getArea(Point3D p1, Point3D p2, Point3D p3)
{
	double a = distanceP1ToP2(p1, p2);
	double b = distanceP1ToP2(p1, p3);
	double c = distanceP1ToP2(p2, p3);
	double p = (a + b + c) / 2;
	double s = sqrt(p*(p - a)*(p - b)*(p - c));
	return s;
}

int main()
{
	int n;
	cin >> n;
	vector<Point3D> vecPoints(n);
	for (auto& e : vecPoints) {
		cin >> e.color >> e.x >> e.y >> e.z;
	}

	double maxArea = -1;
	//三个循环遍历，是比较笨的办法
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j)
			for (int k = j + 1; k < n; ++k) {
				bool con1 = (
					vecPoints[i].color == vecPoints[j].color &&
					vecPoints[i].color == vecPoints[k].color);
				bool con2 = (
					vecPoints[i].color != vecPoints[j].color &&
					vecPoints[i].color != vecPoints[k].color &&
					vecPoints[j].color != vecPoints[k].color);
				if (con1 || con2) {
					double thisArea = getArea(vecPoints[i],
						vecPoints[j], vecPoints[k]);
					if (thisArea > maxArea)
						maxArea = thisArea;
				}
			}
	}

	//注意保留5位小数
	cout.setf(ios::fixed);
	cout << setprecision(5) << maxArea << endl;

	//或
	//注意保留5位小数
	printf("%.5f\n", maxArea);
	return 0;
}