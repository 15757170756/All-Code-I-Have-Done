/***************************************
              7
			 3 8
			8 1 0
		   2 7 4 4
		  4 5 2 6 5
在上面的数字三角形中寻找一条从顶部到底边的路径，
使得路径上所经过的数字之和最大。
路径上的每一步都只能往左下或 右下走。
只需要求出这个最大和即可，不必给出具体路径。 
三角形的行数大于1小于等于100，数字为 0 - 99
输入格式：
5      //表示三角形的行数    接下来输入三角形
7
3   8
8   1   0
2   7   4   4
4   5   2   6   5
要求输出最大和

首先，肯定得用二维数组来存放数字三角形
然后我们用D( r, j) 来表示第r行第 j 个数字(r,j从1开始算)
我们用MaxSum(r, j)表示从D(r,j)到底边的各条路径中，最佳路径的数字之和。
因此，此题的最终问题就变成了求 MaxSum(1,1)
当我们看到这个题目的时候，首先想到的就是可以用简单的递归来解题：
D(r, j)出发，下一步只能走D(r+1,j)或者D(r+1, j+1)。故对于N行的三角形，我们可以写出如下的递归式：
if ( r == N)
MaxSum(r,j) = D(r,j)
else
MaxSum( r, j) = Max{ MaxSum(r＋1,j), MaxSum(r+1,j+1) } + D(r,j)
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
对的，代码运行超时了，为什么会超时呢？
答案很简单，因为我们重复计算了，
当我们在进行递归时，计算机帮我们计算的过程如下图：
就拿第三行数字1来说，
当我们计算从第2行的数字3开始的MaxSum时会计算出从1开始的MaxSum，
当我们计算从第二行的数字8开始的MaxSum的时候又会计算一次从1开始的MaxSum，
也就是说有重复计算。这样就浪费了大量的时间。也就是说如果采用递规的方法，
深度遍历每条路径，存在大量重复计算。则时间复杂度为 2的n次方,对于 n = 100 行，肯定超时。
接下来，我们就要考虑如何进行改进，
我们自然而然就可以想到如果每算出一个MaxSum(r,j)就保存起来，
下次用到其值的时候直接取用，则可免去重复计算。
那么可以用n方的时间复杂度完成计算。
因为三角形的数字总数是 n(n+1)/2
根据这个思路，我们就可以将上面的代码进行改进，
使之成为记忆递归型的动态规划程序：
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
虽然在短时间内就AC了。但是，我们并不能满足于这样的代码，
因为递归总是需要使用大量堆栈上的空间，很容易造成栈溢出，
我们现在就要考虑如何把递归转换为递推，让我们一步一步来完成这个过程。
我们首先需要计算的是最后一行，因此可以把最后一行直接写出，如下图：
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
我们的代码仅仅是这样就够了吗？当然不是，
我们仍然可以继续优化，
而这个优化当然是对于空间进行优化，
其实完全没必要用二维maxSum数组存储每一个MaxSum(r,j),
只要从底层一行行向上递推，
那么只要一维数组maxSum[100]即可,
即只要存储一行的MaxSum值就可以。
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
	maxSum = D[n]; //maxSum指向第n行    
	for (int i = n - 2; i >= 0; --i)
		for (int j = 0; j <= i; ++j)
			maxSum[j] = max(maxSum[j], maxSum[j + 1]) + D[i][j];
	cout << maxSum[0] << endl;
}
