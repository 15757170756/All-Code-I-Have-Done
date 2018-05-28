/*
给定一个正数数组，
找出不相邻元素的子序列的和的最大值。
如：2、5、3、9应该返回14（5+9）；8、5、3、9、1应该返回17（8+9）；
5 4 10 100 10 5应该返回110（5+100+5）；

"输入的第一行指定用例数量T；
用例的第一行输入指定数组长度N；
用例的第二行输入指定N个数组元素C[i]；"

输出子序列的和的最大值

"1 ≤ T ≤ 10
1 ≤ N ≤ 100
1 ≤ C[i] ≤ 500"


Input:
2
6
5 4 10 100 10 5
4
3 2 7 10

Output:
110
13
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

using namespace::std;

struct MaxNum
{
	int num;
	int index;
	MaxNum(int num, int idx) :num(num), index(idx){}
	MaxNum(){}
	bool operator<(const MaxNum &others) const
	{
		return this->num < others.num;
	}

	bool operator>(const MaxNum &others) const
	{
		return this->num > others.num;
	}
};

int find_max_sum_without_adjacents(vector<MaxNum> &vec)
{
	int len = vec.size();
	sort(vec.begin(), vec.end(), greater<MaxNum>());
	//for (int i = 0; i < len; ++i)
	//	cout << vec[i].num << ' ' << vec[i].index << endl;
	int sum = 0;
	vector<MaxNum> auxVec;
	auxVec.emplace_back(vec[0].num, vec[0].index);
	for (int i = 1; i < len; ++i) {
		int idx1 = vec[i].index;
		int sum0 = vec[i].num;
		int cnt = 0;
		for (int j = 0; j < auxVec.size(); ++j) {
			int idx2 = auxVec[j].index;
			if (abs(idx1 - idx2) > 1)
				++cnt;
			else
				break;
		}
		if (cnt == auxVec.size())
			auxVec.emplace_back(sum0, idx1);
	}
	for (int i = 0; i < auxVec.size(); ++i)
		sum += auxVec[i].num;
	return sum;
}

void test1()
{
	freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<MaxNum> vec(n);
		for (int i = 0; i < n; ++i) {
			int temp;
			cin >> temp;
			vec[i].num = temp;
			vec[i].index = i;
		}
		cout << find_max_sum_without_adjacents(vec) << endl;
	}
}


int main(int argc, char* argv[])
{
	test1();
	return 0;
}










#include <stdio.h>
#include <vector>

using namespace std;

int MSNAE(vector<int>& nums) {

	int len = nums.size();
	if (len == 0) {
		return 0;
	}

	int incl = nums[0];      //incl表示当可以包含nums[i]时，前i个元素所能达到的最大值；初始化为第一个元素
	int excl = 0;            //excl表示不包含第nums[i]时，前i个元素所能达到的最大值；初始化为0；
	for (int i = 1; i < len; i++) {
		int temp = incl;
		incl = max(excl + nums[i], incl); //更新incl；1.不包含前一个元素，包括本元素（excl+nums[i]）；2. 不包括本元素（incl）的较大值
		excl = temp;      //excl跟新为可能包括前一个元素的值（一定不包括i所指元素）
	}

	return incl;
}

int main(int argc, const char * argv[]) {

	vector<int> test = { 4, 1, 1, 4, 2, 1 };
	int ans = MSNAE(test);
	printf("%d\n", ans);

	return 0;
}

















class Solution {
public:
	int rob(vector<int>& nums) {
		if (nums.size() == 0)
			return 0;
		if (nums.size() == 1)
			return nums[0];
		if (nums.size() == 2)
			return max(nums[0], nums[1]);
		if (nums.size() == 3)
			return max(nums[0] + nums[2], nums[1]);

		vector<int> max_money(nums.size());
		max_money[0] = nums[0];
		max_money[1] = nums[1];
		max_money[2] = max(nums[0] + nums[2], nums[1]);
		int result = max(max(max_money[0], max_money[1]), max_money[2]);
		for (int i = 3; i < nums.size(); i++)
		{
			max_money[i] = nums[i] + max(max_money[i - 2], max_money[i - 3]);
			result = max(result, max_money[i]);
		}
		return result;
	}
};





















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

using namespace::std;

int find_max_sum_without_adjacents(vector<int> &vec)
{
	if (vec.size() == 0)
		return 0;
	if (vec.size() == 1)
		return vec[0];
	if (vec.size() == 2)
		return max(vec[0], vec[1]);
	if (vec.size() == 3)
		return max(vec[0] + vec[2], vec[1]);

	vector<int> maxNum(vec.size());
	maxNum[0] = vec[0];
	maxNum[1] = vec[1];
	maxNum[2] = max(vec[0] + vec[2], vec[1]);

	int result = max(max(maxNum[0], maxNum[1]), maxNum[2]);
	for (int i = 3; i < vec.size(); ++i) {
		maxNum[i] = vec[i] + max(maxNum[i - 2], maxNum[i - 3]);
		result = max(result, maxNum[i]);
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
		vector<int> vec(n);
		for (int i = 0; i < n; ++i)
			cin >> vec[i];
		cout << find_max_sum_without_adjacents(vec) << endl;
	}
}


int main(int argc, char* argv[])
{
	test1();
	return 0;
}