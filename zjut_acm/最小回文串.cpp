/*
最小回文串 
Time Limit:1000MS  Memory Limit:32768K
Description:
IOI是一个回文串，并且是一个最小回文串。所谓“最小回文串”，
就是指重组字母的排列顺序后能够得到的字典顺序最前的回文串。
例如BAAB是一个回文串，重组字母的排列之后可以得到另一个回文串ABBA，
并且ABBA按照字典顺序应该排在BAAB的前面。 给出一个字符串，
如果不能组合成回文串，则输出“Sorry”；否则输出最小回文串。
Input:
第一行的正整数N（1<=N<=10）表示有N组测试数据。其后N行，
每行都有一个字符串。字符串只由大写字母A-Z组成，并且字符串的长度不超过80
Output:
输出数据有N行，每行对应一组测试数据。
Sample Input:
1
IOI
Sample Output:
IOI
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	int n;
	cin >> n;
	while (n--) {
		string s;
		cin >> s;
		int hashTable[26];
		memset(hashTable, 0, sizeof(hashTable));
		for (int i = 0; i < s.size(); ++i) 
			++hashTable[s[i] - 'A'];
		int oddCnt = 0;
		char oddChar = 0;
		for (int i = 0; i < 26; ++i)
			if (hashTable[i] % 2 == 1) {
				++oddCnt;
				oddChar = i + 'A';
			}
		if (oddCnt > 1) {
			cout << "Sorry\n";
			continue;
		}
		string result(s.size(), ' ');
		
		for (int i = 0, j = 0, k = result.size() - 1;
			i < 26; ++i) {
			if (hashTable[i] > 0) {
				if (hashTable[i] % 2 == 1) {
					int idx = s.size() / 2;
					result[idx] = i + 'A';
					int tmp = (hashTable[i] - 1) / 2;
					int tmpIdx = 1;
					while (tmp--) {
						result[idx + (tmpIdx)] = i + 'A';
						result[idx - (tmpIdx)] = i + 'A';
						++tmpIdx;
					}
				}
				else {
					int tmp = hashTable[i] / 2;
					while (tmp--) {
						result[j++] = i + 'A';
						result[k--] = i + 'A';
					}
				}
			}
		}
		cout << result << endl;
	}

	return 0;
}

/*
input:
5
BBBBAAACCDDEE
IOI
ABCD
AABB
RRTTTREEWW

output:
BBCDEAAAEDCBB
IOI
Sorry
ABBA
Sorry
*/