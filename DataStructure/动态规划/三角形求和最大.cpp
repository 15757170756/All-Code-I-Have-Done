/***************************************
              7
			 3 8
			8 1 0
		   2 7 4 4
		  4 5 2 6 5
�������������������Ѱ��һ���Ӷ������ױߵ�·����
ʹ��·����������������֮�����
·���ϵ�ÿһ����ֻ�������»� �����ߡ�
ֻ��Ҫ���������ͼ��ɣ����ظ�������·���� 
�����ε���������1С�ڵ���100������Ϊ 0 - 99
�����ʽ��
5      //��ʾ�����ε�����    ����������������
7
3   8
8   1   0
2   7   4   4
4   5   2   6   5
Ҫ���������

���ȣ��϶����ö�ά�������������������
Ȼ��������D( r, j) ����ʾ��r�е� j ������(r,j��1��ʼ��)
������MaxSum(r, j)��ʾ��D(r,j)���ױߵĸ���·���У����·��������֮�͡�
��ˣ��������������ͱ������ MaxSum(1,1)
�����ǿ��������Ŀ��ʱ�������뵽�ľ��ǿ����ü򵥵ĵݹ������⣺
D(r, j)��������һ��ֻ����D(r+1,j)����D(r+1, j+1)���ʶ���N�е������Σ����ǿ���д�����µĵݹ�ʽ��
if ( r == N)
MaxSum(r,j) = D(r,j)
else
MaxSum( r, j) = Max{ MaxSum(r��1,j), MaxSum(r+1,j+1) } + D(r,j)
****************************************/


#include <iostream>  
#include <algorithm> 
#define MAX 101  
using namespace std;
int D[MAX][MAX];
int n;
int MaxSum(int i, int j){
	if (i == n)
		return D[i][j];
	int x = MaxSum(i + 1, j);
	int y = MaxSum(i + 1, j + 1);
	return max(x, y) + D[i][j];
}
int main(){
	int i, j;
	cin >> n;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= i; j++)
			cin >> D[i][j];
	cout << MaxSum(1, 1) << endl;
}

/***************************************
�Եģ��������г�ʱ�ˣ�Ϊʲô�ᳬʱ�أ�
�𰸺ܼ򵥣���Ϊ�����ظ������ˣ�
�������ڽ��еݹ�ʱ������������Ǽ���Ĺ�������ͼ��
���õ���������1��˵��
�����Ǽ���ӵ�2�е�����3��ʼ��MaxSumʱ��������1��ʼ��MaxSum��
�����Ǽ���ӵڶ��е�����8��ʼ��MaxSum��ʱ���ֻ����һ�δ�1��ʼ��MaxSum��
Ҳ����˵���ظ����㡣�������˷��˴�����ʱ�䡣Ҳ����˵������õݹ�ķ�����
��ȱ���ÿ��·�������ڴ����ظ����㡣��ʱ�临�Ӷ�Ϊ 2��n�η�,���� n = 100 �У��϶���ʱ��
�����������Ǿ�Ҫ������ν��иĽ���
������Ȼ��Ȼ�Ϳ����뵽���ÿ���һ��MaxSum(r,j)�ͱ���������
�´��õ���ֵ��ʱ��ֱ��ȡ�ã������ȥ�ظ����㡣
��ô������n����ʱ�临�Ӷ���ɼ��㡣
��Ϊ�����ε����������� n(n+1)/2
�������˼·�����ǾͿ��Խ�����Ĵ�����иĽ���
ʹ֮��Ϊ����ݹ��͵Ķ�̬�滮����
****************************************/


#include <iostream>  
#include <algorithm> 
using namespace std;

#define MAX 101

int D[MAX][MAX];
int n;
int maxSum[MAX][MAX];

int MaxSum(int i, int j){
	if (maxSum[i][j] != -1)
		return maxSum[i][j];
	if (i == n)
		maxSum[i][j] = D[i][j];
	else{
		int x = MaxSum(i + 1, j);
		int y = MaxSum(i + 1, j + 1);
		maxSum[i][j] = max(x, y) + D[i][j];
	}
	return maxSum[i][j];
}
int main(){
	int i, j;
	cin >> n;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= i; j++) {
			cin >> D[i][j];
			maxSum[i][j] = -1;
		}
	cout << MaxSum(1, 1) << endl;
}


/***************************************
��Ȼ�ڶ�ʱ���ھ�AC�ˡ����ǣ����ǲ����������������Ĵ��룬
��Ϊ�ݹ�������Ҫʹ�ô�����ջ�ϵĿռ䣬���������ջ�����
�������ھ�Ҫ������ΰѵݹ�ת��Ϊ���ƣ�������һ��һ�������������̡�
����������Ҫ����������һ�У���˿��԰����һ��ֱ��д��������ͼ��
****************************************/
#include <iostream>  
#include <algorithm> 
using namespace std;

#define MAX 101  

int D[MAX][MAX];
int n;
int maxSum[MAX][MAX];
int main(){
	int i, j;
	cin >> n;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= i; j++)
			cin >> D[i][j];
	for (int i = 1; i <= n; ++i)
		maxSum[n][i] = D[n][i];
	for (int i = n - 1; i >= 1; --i)
		for (int j = 1; j <= i; ++j)
			maxSum[i][j] = max(maxSum[i + 1][j], maxSum[i + 1][j + 1]) + D[i][j];
	cout << maxSum[1][1] << endl;
}




/***************************************
���ǵĴ�������������͹����𣿵�Ȼ���ǣ�
������Ȼ���Լ����Ż���
������Ż���Ȼ�Ƕ��ڿռ�����Ż���
��ʵ��ȫû��Ҫ�ö�άmaxSum����洢ÿһ��MaxSum(r,j),
ֻҪ�ӵײ�һ�������ϵ��ƣ�
��ôֻҪһά����maxSum[100]����,
��ֻҪ�洢һ�е�MaxSumֵ�Ϳ��ԡ�
****************************************/
#include <iostream>  
#include <algorithm> 
using namespace std;

#define MAX 101  

int D[MAX][MAX];
int n;
int *maxSum;

int main()
{
	int i, j;
	cin >> n;
	for (i = 0; i < n; i++)
		for (j = 0; j <= i; j++)
			cin >> D[i][j];
	maxSum = D[n]; //maxSumָ���n��    
	for (int i = n - 2; i >= 0; --i)
		for (int j = 0; j <= i; ++j)
			maxSum[j] = max(maxSum[j], maxSum[j + 1]) + D[i][j];
	cout << maxSum[0] << endl;
}
