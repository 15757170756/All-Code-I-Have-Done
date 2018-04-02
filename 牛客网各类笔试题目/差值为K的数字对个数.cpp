/*
Python简简单单通过
*/

def diff(listt, k) :
newlist = [i + k for i in listt]
print set(listt)
print set(newlist)
print set(listt) & set(newlist)
return len(set(listt) & set(newlist))

s = raw_input()
string = raw_input()

n, k = s.split()
n = int(n)
k = int(k)

listt = []
for sttrr in string.split() :
listt.append(int(sttrr))
print diff(listt, k)




#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <unordered_map>

using namespace::std;

int diff(vector<int> &vec, int k)
{
	unordered_map<int, int> m;
	for (int i = 0; i < vec.size(); ++i)
		m[vec[i]] = i;

	map<int, int> map1;
	for (int i = 0; i < vec.size(); ++i) {
		int t = abs(vec[i] - abs(k));
		if (m.count(t) && m[t] != i)
			map1.emplace(i, m[t]);
	}

	//for (int i = 0; i < vec.size(); ++i) {
	//	for (int j = i + 1; j < vec.size(); ++j) {
	//		if (abs(vec[i] - vec[j]) == abs(k)) {
	//			map1.emplace(vec[i], vec[j]);
	//		}
	//	}
	//}
	return map1.size();
}

int main(int argc, char* argv[])
{
	ifstream in("input.txt");
	int n, k;
	cin >> n >> k;
	vector<int> vec(n);
	for (int i = 0; i < n; ++i)
		cin >> vec[i];

	cout << diff(vec, k) << endl;


	return 0;
}
/*
通过80%
*/








/*
这是根据Python程序写的，
早知道就应该这么改了，这样估计
能ACE
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <unordered_map>
#include <set>

using namespace::std;

int diff(vector<int> &vec, int k)
{
	vector<int> vecK(vec.size());
	for (int i = 0; i < vec.size(); ++i)
		vecK[i] = vec[i] + k;

	set<int> vecSet(vec.begin(), vec.end());
	set<int> vecSetK(vecK.begin(), vecK.end());

	vector<int> resultVec;
	for (set<int>::const_iterator iter = vecSet.begin();
		iter != vecSet.end(); ++iter) {
		auto searchIter = vecSetK.find(*iter);
		if (searchIter != vecSetK.end())
			resultVec.emplace_back(*iter);
	}

	return resultVec.size();
}

int main(int argc, char* argv[])
{
	ifstream in("input.txt");
	int n, k;
	cin >> n >> k;
	vector<int> vec(n);
	for (int i = 0; i < n; ++i)
		cin >> vec[i];

	cout << diff(vec, k) << endl;


	return 0;
}
















https://blog.csdn.net/flushhip/article/details/79685488


作者：vegetableB
链接：https ://www.nowcoder.com/discuss/70299
来源：牛客网

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 7;
int a[N];
int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
	sort(a, a + n);
	n = unique(a, a + n) - a;
	int r = 0, ans = 0;
	for (int l = 0; l < n; ++l)
	{
		while (r < n&&a[r] - a[l] < k) ++r;
		if (r == n) break;
		if (a[r] - a[l] == k) ++ans;
	}
	printf("%d\n", ans);
	return 0;
}
