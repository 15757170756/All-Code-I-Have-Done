/*
* Filename :coins.cpp
* Description: solve coin combinations using dynamic programing
* Complier: g++
* Author: python27

http://www.cnblogs.com/python27/p/3303721.html
*/
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

/****************************************************************
* coin Combinations: using dynamic programming
*
* Basic idea:
* dp[i][j] = sum(dp[i-1][j-k*coins[i-1]]) for k = 1,2,..., j/coins[i-1]
* dp[0][j] = 1 for j = 0, 1, 2, ..., sum
*
* Input:
* coins[] - array store all values of the coins
* coinKinds - how many kinds of coins there are
* sum - the number you want to construct using coins
*
* Output:
* the number of combinations using coins construct sum
*
* Usage:
* c[3] = {1, 2, 5};
* int result = coinCombinations(c, 3, 10);
*
****************************************************************/
int coinCombinations(int coins[], int coinKinds, int sum)
{
	// 2-D array using vector: is equal to: dp[coinKinds+1][sum+1] = {0};
	vector<vector<int> > dp(coinKinds + 1);
	for (int i = 0; i <= coinKinds; ++i)
	{
		dp[i].resize(sum + 1);
	}
	for (int i = 0; i <= coinKinds; ++i)
	{
		for (int j = 0; j <= sum; ++j)
		{
			dp[i][j] = 0;
		}
	}

	//init: dp[i][0] = 1; i = 0, 1, 2 ..., coinKinds
	//Notice: dp[0][0] must be 1, althongh it make no sense that
	//using 0 kinds of coins construct 0 has one way. but it the foundation
	//of iteration. without it everything based on it goes wrong
	for (int i = 0; i <= coinKinds; ++i)
	{
		dp[i][0] = 1;
	}

	// iteration: dp[i][j] = sum(dp[i-1][j - k*coins[i-1]])
	// k = 0, 1, 2, ... , j / coins[i-1]
	for (int i = 1; i <= coinKinds; ++i)
	{
		for (int j = 1; j <= sum; ++j)
		{
			dp[i][j] = 0;
			for (int k = 0; k <= j / coins[i - 1]; ++k)
			{
				dp[i][j] += dp[i - 1][j - k * coins[i - 1]];
			}
		}
	}

	return dp[coinKinds][sum];
}

int main()
{
	int coins[8] = { 1, 2, 5, 10, 20, 50, 100, 200 };
	int sum = 200;
	int result = coinCombinations(coins, 8, 200);
	cout << "using 8 kinds of coins construct 200, combinations are: " << endl;
	cout << result << endl;
	return 0;
}