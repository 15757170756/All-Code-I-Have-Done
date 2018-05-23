/*
给定一个全小写的英文字符串，请在该字符串中找到一个连续子字符串，
使得子字符串没有重复的字符并且长度最长，计算此最长字符串的长度。
比如：abcbdeab,最长的子字符串为cbdea，长度为5；
aaaa，最长子字串为a，长度为1。

1<=length of str<=100

Input:
3
abcbdeab
abcabcdabc
bbbb

Output:
4
1
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

int lengthOfLongestSubstring(string s) {
	set<char> norep;
	int ans = 0;
	for (int i = 0, j = 0; i < s.size();){
		//如果字符不存在，插入到set中
		if (norep.count(s[i]) == 0)
			norep.insert(norep.end(), s[i++]);
		//set是有序的，我们想从头开始删除字符，按着s的顺序删除，而不是set的顺序。
		else 
			norep.erase(s[j++]);
		ans = max(ans, int(norep.size()));
	}
	return ans;
}

void test1()
{
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	while (t--) {
		string str;
		cin >> str;
		cout << lengthOfLongestSubstring(str) << endl;
	}

}


int main(int argc, char* argv[])
{
	test1();
	return 0;
}