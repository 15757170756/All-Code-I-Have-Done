/*
93. Restore IP Addresses
DescriptionHintsSubmissionsDiscussSolution
Given a string containing only digits, restore it by returning all possible valid IP address combinations.

Example:

Input: "25525511135"
Output: ["255.255.11.135", "255.255.111.35"]
Seen this question in a real interview before?  
Subscribe to see which companies asked this question.

Related Topics 

Similar Questions 
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

void dfs(string s, int start, int step, string ip, vector<string>& result)
{
	if (start == s.size() && step == 4) {
		ip.erase(ip.end() - 1); //remove the last '.' from the last decimal number
		result.push_back(ip);
		return;
	}
	if (s.size() - start > (4 - step) * 3) return;
	if (s.size() - start < (4 - step)) return;
	int num = 0;
	for (int i = start; i < start + 3; i++) {
		num = num * 10 + (s[i] - '0');
		if (num <= 255) {
			ip += s[i];
			dfs(s, i + 1, step + 1, ip + '.', result);
		}
		if (num == 0) break;
	}
}

vector<string> restoreIpAddresses(string s) {
	vector<string> result;
	string ip;
	dfs(s, 0, 0, ip, result); //paras:string s,start index of s,step(from0-3),intermediate ip,final result
	return result;
}



int main(int argc, char* argv[])
{
	long long n;
	cin >> n;
	string s = to_string(n);
	cout << restoreIpAddresses(s).size() << endl;
	
	return 0;
}