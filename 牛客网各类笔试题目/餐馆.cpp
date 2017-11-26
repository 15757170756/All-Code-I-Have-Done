/***************************************
��Ŀ����

ĳ�͹���n�����ӣ�ÿ��������һ��������a�����ɵ������������m�����ˣ�ÿ������������������b������cԤ�����ѽ��ڲ�����ƴ��������£���ʵ��һ���㷨ѡ������һ���ֿ��ˣ�ʹ����Ԥ�����ѽ�����

��������

�������m+2�С�
��һ�а���2������n(1<=n<=50000)��m(1<=m<=50000);
�ڶ���Ϊn������a����ÿ�����ӿ����ɵ�����������Կո�ָ�����Χ����32λint��Χ��;
������m�У�ÿ����������b��c���ֱ��ʾ��i�����˵�������Ԥ�����ѽ�
�Կո�ָ�����Χ����32λint��Χ�ڡ�
�������

���һ����������ʾ������Ԥ�����ѽ�
��������

3 5
2 4 2
1 3
3 5
3 7
5 9
1 10
�������

20

����:

̰�ķ����Ȱѹ˿ͽ������ѽ���,������������ 
Ȼ��ö��ÿ���˿�ȥ���ֵ�ǰ���ʺϵ� ���ӵ�������
ά���𰸼���,ע��𰸿��ܱ�int�������㱩�������ˡ�
���ܲ�����ʱ�临�Ӷȣ�O(mlogm + nlogm)
ע��: �����Ҫʹ��long long(��Ӧprintf�ĸ�ʽ����Ϊ%lld), 
���������long long, ����ֻ��ͨ��50%��
****************************************/
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct node{
	int b, c;
};
int comp(node x, node y){
	if (x.c == y.c) {
		return x.b < y.b;
	}
	return x.c > y.c;
}
int n, m;
long long ans;
std::vector<node> v;
std::multimap<int, int> mp;
int main(){
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++){
		int x; scanf("%d", &x);
		mp.insert(std::pair<int, int>(x, 1));
	}
	for (int i = 0; i < m; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		node tmp;
		tmp.b = x, tmp.c = y;
		v.push_back(tmp);
	}
	sort(v.begin(), v.end(), comp);
	for (int i = 0; i < m; i++){
		std::map<int, int>::iterator it = mp.lower_bound(v[i].b);
		if (it != mp.end()) {
			mp.erase(it);
			ans += v[i].c;
		}
	}
	printf("%lld\n", ans);
}