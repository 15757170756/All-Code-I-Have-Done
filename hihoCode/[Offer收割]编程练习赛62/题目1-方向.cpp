/*
题目1 : 方向
时间限制:20000ms
单点时限:1000ms
内存限制:256MB
描述
我们可以用 0..359 之间的角度来描述一个方向，现在给出两个方向 a , b，你需要求出，从 a 转到 b 最少需要的角度。

例如，从 70° 转到 180°，可以转 110°，也可以转 -250°

又比如，从315°转到45°，可以转90°，也可以转 -270°

定义一个角度 a 比另一个角度 b 小，当且仅当 a 的绝对值小于 b。

例如：180°比 -220°小，-45°比80°小。

特别的，如果两个角度的绝对值相同，我们规定正的角度比较小，比如180°小于-180°

输入
第一行两个 0 到 359之间的整数 a , b

输出
输出最少需要转的角度

额外的样例
样例输入1	样例输出1
180 270
90
样例输入2	样例输出2
45 270
-135
样例输入
315 45
样例输出
90
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


int main(int argc, char* argv[])
{
	//freopen("input.txt", "r", stdin);
	//while (1) {
		int a, b;
		scanf("%d%d", &a, &b);
		if (a >= 0 && a <= 359 && b >= 0 && b <= 359) {
			int ab = a - b;
			int ba = b - a;
			if (ba > 0 && ba < 180)
				printf("%d\n", ba);
			else if (ba > 180)
				printf("%d\n", ba - 360);
			else if (ba < -180)
				printf("%d\n", ba + 360);
			else if (ba > -180 && ba <= 0)
				printf("%d\n", ba);
			else if (ba == 180 || ba == -180)
				printf("%d\n", abs(ba));
		}
	//}
	return 0;
}



/*
结果:Accepted 
得分:100 / 100

*/