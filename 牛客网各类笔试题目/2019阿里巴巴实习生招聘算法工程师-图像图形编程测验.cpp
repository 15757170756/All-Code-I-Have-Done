/*
将一个圆形等分城N个小扇形，将这些扇形标记为1，2，3,…，N。
现在使用M种颜色对每个扇形进行涂色，每个扇形涂一种颜色，且相邻的扇形颜色不同。
求：有多少种涂色方法。
备注：1，不考虑数值越界的情况。
2，N>=1, M>=3。
3，一个例子：如果N=3，M=3时，一共有6种涂法。
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <cmath>

using namespace std;

/** 请完成下面这个函数，实现题目要求的功能 **/
/** 当然，你也可以不按照这个模板来作答，完全按照自己的想法来 ^-^  **/
int Colour(int split_part, int colour_number)
{
	if (1 == split_part)
		return colour_number;

	else if (2 == split_part)
		return colour_number*(colour_number - 1);

	int res = colour_number * pow(colour_number - 1, split_part - 1) -
		Colour(colour_number, split_part - 1);

	return res;
}

int main() {
	while (1) {
		int res;
		int _split_part;
		cin >> _split_part;

		int _colour_number;
		cin >> _colour_number;

		res = Colour(_split_part, _colour_number);
		cout << res << endl;
	}

	return 0;

}





