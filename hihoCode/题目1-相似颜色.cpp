/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
在CSS中我们可以用井号(#)加6位十六进制数表示一种颜色，
例如#000000是黑色，#ff0000是红色，#ffd700是金色。

同时也可以将六位颜色#RRGGBB简写为#RGB三位颜色。
例如#000与#000000是相同的，#f00与#ff0000是相同的，#639与#663399是相同的。

对于两个颜色#abcdef和#ghijkl，
我们定义其距离是(ab - gh)2 + (cd - ij)2 + (ef - kl)2。
(其中ab, cd, ef, gh, ij, kl都是十六进制数，也即0~255的整数)

给定一个六位颜色#abcdef，请你求出距离它最近的三位颜色#rgb。

输入
#abcdef

其中abcdef是'0'-'9'或'a'-'f'。

输出
距离输入颜色最近的#rgb

样例输入
#40e0d0
样例输出
#4dc
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <climits>

using namespace::std;

int main()
{
	vector<string> rgb = { "00", "11", "22", "33", "44", "55", "66", "77",
		"88", "99", "aa", "bb", "cc", "dd", "ee", "ff" };
	string s;// = "#40e0d0";;
	cin >> s;
	vector<string> rrggbb;
	vector<string> result;
	result.assign(3, "");
	rrggbb.push_back(s.substr(1, 2));
	rrggbb.push_back(s.substr(3, 2));
	rrggbb.push_back(s.substr(5, 2));
	for (int i = 0; i < rrggbb.size(); ++i) {
		//cout << rrggbb[i] << endl;
		int rrggbbInt = stoi(rrggbb[i], 0, 16);
		//cout << rrggbbInt << endl;
		int minDis = INT_MAX;
		for (int j = 0; j < rgb.size(); ++j) {
			int rgbInt = stoi(rgb[j], 0, 16);
			int thisDis = (rrggbbInt - rgbInt)*(rrggbbInt - rgbInt);
			if (minDis > thisDis) {
				minDis = thisDis;
				result[i] = rgb[j];
				//cout << result[i] << endl;
			}
		}
	}

	cout << '#';
	for (int i = 0; i < result.size(); ++i)
		cout << result[i][0];
}

/*
结果:Accepted
得分:100 / 100
*/