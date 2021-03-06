﻿/*
时间限制：1秒

空间限制：32768K

度度熊有一个N个数的数组，他想将数组从小到大排好序，
但是萌萌的度度熊只会下面这个操作：
任取数组中的一个数然后将它放置在数组的最后一个位置。
问最少操作多少次可以使得数组从小到大有序？
输入描述 :
首先输入一个正整数N，接下来的一行输入N个整数。
(N <= 50, 每个数的绝对值小于等于1000)

输出描述 :
输出一个整数表示最少的操作次数。

 输入例子1 :
4
19 7 8 25

输出例子1 :
2
*/

//牛客网上面别人的代码

/*
分析：
根据题目要求，意思是两个数如果较大的数在前面，
就需要将其移到数组最后面，要想移动次数最少，
显然就需要有每次移动是规律可行的。
比如输入例子：19 7 8 25，
最快的移动方法就是首先将19移到最后变为 _ 7 8 25 19，
然后将25移到最后变为_ 7 8 _  19  25, 
只需移动两次即可使数组从小到大有序
（下划线表示原始元素位置或数组后新增加的位置）。
如果是按从小到大的元素依次往后移动，
即7 8  19 25分别往数组最后位置移动，虽然也可以使元素有序，
但是移动次数为4次，这样做并不是效率最高的，
因为原始的7和8已经有序了，是不需要再移动的。

从上面分析，我们就应该会想到，如果从最小的元素开始，
后面的元素如果是有序的，我们是不要移动的，
如果大的数在前面就需要移到后面去。

如果我们将数组元素从小到大排序，然后也知道了其在原始数组的位置，
那我们可以最小的元素开始。与第二小的元素进行比较，
如果说最大元素在数组中的下标位置大于第二小元素在数组中的下标，
即最小元素在第二小元素的后面，
那我们就需要将第二小元素移到数组的最后面去，
这样才能保证最小的数组元素在前面，
依次比较第二小元素和第三小元素在原始数组的下标位置，
如果第二小元素在数组中的下标位置大于第三小元素在数组中的下标，
将第三小元素移到数组最后面去，依次执行下去。。。*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main()
{
	int n, temp;
	cin >> n;
	vector<int> arrVec;
	map<int, int> arrMap;
	for (int i = 0; i < n; ++i) {
		cin >> temp;
		arrVec.push_back(temp);
		arrMap[temp] = i;
	}

	sort(arrVec.begin(), arrVec.end());
	int t = n, count = 0;
	for (int i = 0; i < n - 1; ++i) {
		if (arrMap[arrVec[i]] > arrMap[arrVec[i + 1]]) {
			arrMap[arrVec[i + 1]] = t++;
			++count;
		}
	}

	cout << count << endl;
	return 0;
}








/*
后来自己又写了一下，
感觉还是得多练习
*/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>

using namespace::std;

void argSort(vector<int>& arrayIn, vector<int>& argcOut)
{
	multimap<int, int> intMap;
	for (int i = 0; i < arrayIn.size(); ++i)
		intMap.emplace(arrayIn[i], i);
	for (multimap<int, int>::const_iterator iter = intMap.begin();
		iter != intMap.end(); ++iter)
		argcOut.emplace_back(iter->second);
}


int main(int argc, char* argv[])
{
	int n;
	cin >> n;
	vector<int> vec(n);
	for (auto& e : vec)
		cin >> e;

	vector<int> argVec;
	argSort(vec, argVec);
	int cnt = 0;
	for (int i = 0; i < n - 1; ++i) {
		int diff = argVec[i + 1] - argVec[i];
		if (diff == 1)
			++cnt;
	}

	int result = n - 1 - cnt;
	cout << result << endl;

	return 0;
}
/*
您的代码已保存
答案错误:您提交的程序没有通过所有的测试用例
case通过率为60.00%

测试用例:
9
2 1 3 4 5 6 7 8 9

对应输出应该为:
8
你的输出为:
2
*/