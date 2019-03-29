/*
In a deck of cards, each card has an integer written on it.

Return true if and only if you can choose X >= 2 such that it is possible to split the entire deck into 1 or more groups of cards, where:

Each group has exactly X cards.
All the cards in each group have the same integer.
 

Example 1:

Input: [1,2,3,4,4,3,2,1]
Output: true
Explanation: Possible partition [1,1],[2,2],[3,3],[4,4]
Example 2:

Input: [1,1,1,2,2,2,3,3]
Output: false
Explanation: No possible partition.
Example 3:

Input: [1]
Output: false
Explanation: No possible partition.
Example 4:

Input: [1,1]
Output: true
Explanation: Possible partition [1,1]
Example 5:

Input: [1,1,2,2,2,2]
Output: true
Explanation: Possible partition [1,1],[2,2],[2,2]

Note:

1 <= deck.length <= 10000
0 <= deck[i] < 10000
*/

class Solution {
public:
	int gcd(int a, int b)
	{
		if (b == 0)
			return a;
		else
			return gcd(b, a%b);
	}

	bool hasGroupsSizeX(vector<int>& deck) 
	{
		const int maxn = 10005;
		int arr[maxn];
		memset(arr, 0, sizeof(arr));
		unordered_map<int, int> unmap;
		for (int i = 0; i < deck.size(); ++i) {
			arr[deck[i]]++;
		}
		int min_num = 0xffff;
		for (int i = 0; i < maxn; ++i) {
			if (arr[i] == 1)
				return false;
			if (arr[i] > 0 && arr[i] < min_num)
				min_num = arr[i];
			//cout << unmap[deck[i]] << ' ';
		}
		int cnt1 = 0, cnt2 = 0;
		int gcd_num = arr[0];
		for (int i = 1; i < maxn; ++i) {
			if (arr[i] > 0) {
				gcd_num = gcd(arr[i], gcd_num);
			}
		}
		
		if (gcd_num > 1)
			return true;
	//	cout << endl;
		return false;
	}
};