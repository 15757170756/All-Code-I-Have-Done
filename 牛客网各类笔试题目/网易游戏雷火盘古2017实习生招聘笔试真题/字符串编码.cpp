/*
时间限制：1秒

空间限制：32768K

给定一个字符串，请你将字符串重新编码，
将连续的字符替换成“连续出现的个数+字符”。
比如字符串AAAABCCDAA会被编码成4A1B2C1D2A。
输入描述:
每个测试输入包含1个测试用例
每个测试用例输入只有一行字符串，字符串只包括大写英文字母，长度不超过10000。


输出描述:
输出编码后的字符串

输入例子1:
AAAABCCDAA

输出例子1:
4A1B2C1D2A
*/


#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdint>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <sstream>

using namespace::std;


int main(int argc, char *argv[])
{
	freopen("input.txt", "r", stdin);
	string str;
	cin >> str;
	string result;
	int cnt = 1;
	for (int i = 0; i < str.length() - 1;++i) {
		cnt = 1;
		while (str[i] == str[i + 1]) {
			++i;
			++cnt;
		}
		string tmp = to_string(cnt);
		result.append(tmp), result.push_back(str[i]);
	}
	cout << result << endl;
	return 0;
}
/*
您的代码已保存
答案错误:您提交的程序没有通过所有的测试用例
case通过率为81.00%
如果最后一个是单个字母就会出错，一定要考虑边界问题
*/



#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdint>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <sstream>

using namespace::std;

int main(int argc, char *argv[])
{
	//freopen("input.txt", "r", stdin);
	string str;
	cin >> str;
	string result;
	int cnt = 1;
	for (int i = 0; i < str.length() - 1; ++i) {
		cnt = 1;
		while (str[i] == str[i + 1]) {
			++i;
			++cnt;
		}
		string tmp = to_string(cnt);
		result.append(tmp), result.push_back(str[i]);
	}
	if (str[str.length() - 2] != str[str.length() - 1])
		result.append(to_string(1)), result.push_back(str[str.length() - 1]);
	cout << result << endl;
	return 0;
}

/*
您的代码已保存
答案正确:恭喜！您提交的程序通过了所有的测试用例
*/