#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <iterator>

using namespace::std;

string Solution(string &s, vector<string> &dic)
{
	map<int, string> map1;
	string result = s;
	vector<int> index, dicIndex;
	string mark1 = "<b>", mark2 = "</b>";
	string::size_type n1, n2;
	int dicLen = dic.size();
	if (dicLen > 1) {
		for (int i = 0; i < dicLen - 1; ++i) {
			string tempStr1 = dic[i];
			string tempStr2 = dic[i + 1];
			n1 = s.find(tempStr1);
			n2 = s.find(tempStr2);
			//cout << n1 << ' ' << n2 << endl;
			if (string::npos != n1)
				map1[n1] = tempStr1;
			if (string::npos != n2)
				map1[n2] = tempStr2;
		}
		vector<string> vecStr;
		vector<int> index;
		for (map<int, string>::const_iterator iter = map1.begin();
			iter != map1.end(); ++iter) {
			cout << iter->first << ' ' << iter->second << endl;
			//cout << (iter++)->first << ' ' << (iter++)->second << endl;
			index.push_back(iter->first);
			vecStr.push_back(iter->second);
		}

		if (map1.size() == 1) {
			result.insert(index[0], mark1);
			result.insert(index[0] + vecStr[0].size() + mark1.size(), mark2);
		}
		else {
			result.insert(index[0], mark1);
			int cnt = 0;
			for (int i = 0; i < index.size() - 1; ++i) {
				int d = index[i + 1] - index[i];
				if (d <= vecStr[i].size())
					continue;
				else {
					result.insert(index[i] + vecStr[i].size() + (i + 1)*mark1.size(), mark2);
					result.insert(index[i + 1] + (i + 1)*(mark2.size() + mark1.size()), mark1);
					++cnt;
				}
			}
			int lastInsert = index[index.size() - 1] + vecStr[index.size() - 1].size() +
				mark1.size() + cnt*(mark1.size() + mark2.size());
			result.insert(lastInsert, mark2);
		}
	}

	return result;
}

int main()
{
	string s1 = "abcxyz123";
	vector<string> dic1 = { "123", "abcd", "xyz" };

	string s2 = "aaabbcc";
	vector<string> dic2 = { "aaa", "aab", "bc", "abb" };

	string result = Solution(s1, dic1);
	cout << result << endl << endl;

	result = Solution(s2, dic2);
	cout << result << endl;
}
