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