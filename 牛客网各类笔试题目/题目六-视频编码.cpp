/*
"在H.264视频编码标准中，编码帧由NALU头和NALU主体组成，其中NALU头由一个字节组成。
在实际编码时，在每个NAL前添加起始码 0x000001，解码器在码流中检测到起始码，当前NAL结束。
为了防止NAL内部出现0x000001的数据，在编码完一个NAL时，
如果检测出有连续两个0x00字节，就在后面插入一个0x03。
当解码器在NAL内部检测到0x000003的数据，就把0x03抛弃，恢复原始数据。
给定一组包含SPS NALU的编码数据，找出解码后的SPS数据。比如：
输入：{0x1f 0x00 0x00 0x01 0x67 0x42 0xd0 0x80 0x00 0x00 0x03 0x00 0x80 0x00 0x0f 0x00 0x00 0x01 0x68 0xce 0x3c 0x80},
处理：在上述例子中，第一个0x00 0x00 0x01为识别到的数据头，
0x00 0x00 0x03 0x00数据中，0x03为需抛弃数据，第二个0x00 0x00 0x01为下一个数据头，
那么取出两个数据头中间的数据并且抛弃掉此0x03，结果如下：
{0x67 0x42 0xd0 0x80 0x00 0x00 0x00 0x80 0x00 0x0f }。"

"输入的第一行指定用例的数量T；
用例的第一行输入指定二进制数据长度N；
用例的第二行输入指定N个二进制数据元素C[i]；"

输出解码后的SPS数据

"7 ≤ N ≤ 50
0 ≤ C[i] ≤ 0xff"

"int find_sps_in_h264(unsigned char[],int N)
input:
1
23
0 0 01 67 42 c0 16 d0 80 0 0 03 0 80 0 0f 0 0 01 68 ce 3c 80
output:
67 42 c0 16 d0 80 0 0 0 80 0 0f"


4
23
0 0 01 67 42 c0 16 d0 80 0 0 03 0 80 0 0f 0 0 01 68 ce 3c 80
23
0 0 01 67 42 c0 0 0 03 16 d0 80 0 0 03 0 80 0 0f 0 0 0 03 0 0 01 68 ce 3c 80
23
0 0 01 67 42 c0 16 d0 80 0 0 03 0 80 0 0f 0 0 68 ce 3c 80
34
1f 0 0 01 67 42 c0 16 d0 80 0 0 01 0 0 03 0 80 0 0f 0 0 0 01 0 68 ce 3c 80
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

using namespace::std;

string decode(string &s)
{
	string startendStr = "0 0 01";
	string eraseStr = "0 0 03";
	string result;
	int start = s.find(startendStr) + startendStr.length() + 1;
	//cout << start << endl;
	int end = s.find(startendStr, start) - 2;
	if (end == -3)
		result = s.substr(start);
	else
		result = s.substr(start, end - start + 1);
	//cout << result << endl;
	for (int i = 0; i < result.size();) {
		int idx = result.find(eraseStr, i);
		if (idx == string::npos)
			break;
		result.erase(idx + 3, 3);
		i += idx;
	}
	return result;
}

void test1()
{
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		getchar();
		string s;
		getline(cin, s);
		string result = decode(s);
		cout << result << endl;
		/*	for (int i = 0; i < result.length(); ++i)
		cout << result[i] << endl;
		cout << endl;*/
	}
}

int main(int argc, char* argv[])
{
	test1();

}