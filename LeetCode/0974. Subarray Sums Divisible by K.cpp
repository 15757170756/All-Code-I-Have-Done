/*
https://leetcode.com/problems/subarray-sums-divisible-by-k/

974. Subarray Sums Divisible by K
Medium

80

4

Favorite

Share
Given an array A of integers, return the number of (contiguous, non-empty) subarrays that have a sum divisible by K.

 

Example 1:

Input: A = [4,5,0,-2,-3,1], K = 5
Output: 7
Explanation: There are 7 subarrays with a sum divisible by K = 5:
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
 

Note:

1 <= A.length <= 30000
-10000 <= A[i] <= 10000
2 <= K <= 10000
Accepted
3,248
Submissions
9,038
*/

class Solution {
public:
	int subarraysDivByK(vector<int>& A, int K) {
		vector<long long int> psum(A.size());
		int res = 0;
		partial_sum(A.begin(), A.end(), psum.begin());
		for (int i = 0; i < psum.size(); ++i)
			if (psum[i] % K == 0)
				++res;
		for (int i = 0; i < psum.size(); ++i) {
			for (int j = i+1; j < psum.size(); ++j) {
				if ((psum[j] - psum[i]) % K == 0)
					++res;
			}
		}
		return (res);
	}
};
//Time Limit Exceeded  留下了没有技术的眼泪 o(╥﹏╥)o 





/*
Solution
Approach 1: Prefix Sums and Counting
Intuition

As is typical with problems involving subarrays, we use prefix sums to add each subarray. Let P[i+1] = A[0] + A[1] + ... + A[i]. Then, each subarray can be written as P[j] - P[i] (for j > i). Thus, we have P[j] - P[i] equal to 0 modulo K, or equivalently P[i] and P[j] are the same value modulo K.

Algorithm

Count all the P[i]'s modulo K. Let's say there are C_xC 
x
​	
  values P[i] \equiv x \pmod{K}P[i]≡x(modK). Then, there are \sum_x \binom{C_x}{2}∑ 
x
​	
 ( 
2
C 
x
​	
 
​	
 ) possible subarrays.

For example, take A = [4,5,0,-2,-3,1]. Then P = [0,4,9,9,7,4,5], and C_0 = 2, C_2 = 1, C_4 = 4C 
0
​	
 =2,C 
2
​	
 =1,C 
4
​	
 =4:

With C_0 = 2C 
0
​	
 =2 (at P[0]P[0], P[6]P[6]), it indicates \binom{2}{2} = 1( 
2
2
​	
 )=1 subarray with sum divisible by KK, namely A[0:6] = [4, 5, 0, -2, -3, 1]A[0:6]=[4,5,0,−2,−3,1].
With C_4 = 4C 
4
​	
 =4 (at P[1]P[1], P[2]P[2], P[3]P[3], P[5]P[5]), it indicates \binom{4}{2} = 6( 
2
4
​	
 )=6 subarrays with sum divisible by KK, namely A[1:2]A[1:2], A[1:3]A[1:3], A[1:5]A[1:5], A[2:3]A[2:3], A[2:5]A[2:5], A[3:5]A[3:5].






A simple solution for this problem is to one by one calculate sum of all sub-arrays possible and check divisible by K. The time complexity for this approach will be O(n^2).

An efficient solution is based on below observation.



Let there be a subarray (i, j) whose sum is divisible by k
  sum(i, j) = sum(0, j) - sum(0, i-1)
Sum for any subarray can be written as q*k + rem where q 
is a quotient and rem is remainder
Thus,     
    sum(i, j) = (q1 * k + rem1) - (q2 * k + rem2)
    sum(i, j) = (q1 - q2)k + rem1-rem2
     
We see, for sum(i, j) i.e. for sum of any subarray to be
divisible by k, the RHS should also be divisible by k.
(q1 - q2)k is obviously divisible by k, for (rem1-rem2) to 
follow the same, rem1 = rem2 where
    rem1 = Sum of subarray (0, j) % k
    rem2 = Sum of subarray (0, i-1) % k 
So if any sub-array sum from index i’th to j’th is divisible by k then we can saya[0]+…a[i-1] (mod k) = a[0]+…+a[j] (mod k)

The above explanation is provided by Ekta Goel.

So we need to find such a pair of indices (i, j) that they satisfy the above condition. Here is the algorithm :

Make an auxiliary array of size k as Mod[k] . This array holds the count of each remainder we are getting after dividing cumulative sum till any index in arr[].
Now start calculating cumulative sum and simultaneously take it’s mod with K, whichever remainder we get increment count by 1 for remainder as index in Mod[] auxiliary array. Sub-array by each pair of positions with same value of ( cumSum % k) constitute a continuous range whose sum is divisible by K.
Now traverse Mod[] auxiliary array, for any Mod[i] > 1 we can choose any to pair of indices for sub-array by (Mod[i]*(Mod[i] – 1))/2 number of ways . Do the same for all remainders < k and sum up the result that will be the number all possible sub-arrays divisible by K.
filter_none
*/

class Solution {
public:
	int subarraysDivByK(vector<int>& A, int K) {
		int N = A.size();
		vector<int> P(N + 1, 0);
		for (int i = 0; i < N; ++i)
			P[i + 1] = P[i] + A[i];
		vector<int> count(K);
		for (int x : P)
			count[(x%K + K) % K]++;
		int ans = 0;
		for (int v : count)
			ans += v*(v - 1) / 2;
		return ans;
	}
};
/*
Success
Details 
Runtime: 64 ms, faster than 20.00% of C++
 online submissions for Subarray Sums Divisible by K.
*/

//python大法
class Solution(object):
    def subarraysDivByK(self, A, K):
        P = [0]
        for x in A:
            P.append((P[-1] + x) % K)// -2 % 5 = 3

        count = collections.Counter(P)
        return sum(v*(v-1)/2 for v in count.values())