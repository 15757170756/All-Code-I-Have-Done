/*
Given an integer array A, and an integer target, return the number of tuples i, j, k  such that i < j < k and A[i] + A[j] + A[k] == target.

As the answer can be very large, return it modulo 10^9 + 7.

 

Example 1:

Input: A = [1,1,2,2,3,3,4,4,5,5], target = 8
Output: 20
Explanation: 
Enumerating by the values (A[i], A[j], A[k]):
(1, 2, 5) occurs 8 times;
(1, 3, 4) occurs 8 times;
(2, 2, 4) occurs 2 times;
(2, 3, 3) occurs 2 times.
Example 2:

Input: A = [1,1,2,2,2,2], target = 5
Output: 12
Explanation: 
A[i] = 1, A[j] = A[k] = 2 occurs 12 times:
We choose one 1 from [1,1] in 2 ways,
and two 2s from [2,2,2,2] in 6 ways.
 

Note:

3 <= A.length <= 3000
0 <= A[i] <= 100
0 <= target <= 300
Seen this question in a real interview before?
*/

class Solution {
public:
	int threeSumMulti(vector<int>& nums, int target) {
		const int mod = 1e9 + 7;
		typedef long long ll;
		ll res = 0;
		int len = nums.size();
		sort(nums.begin(), nums.end());
		for (int i = 0; i < len; ++i) {
			int this_target = target - nums[i];
			int front = i + 1;
			int back = len - 1;

			while (front < back) {
				int sum = nums[front] + nums[back];
				if (sum < this_target)
					++front;
				else if (sum > this_target)
					--back;
				else {
					vector<int> triplet(3, 0);
					triplet[0] = nums[i];
					triplet[1] = nums[front];
					triplet[2] = nums[back];
					//res.push_back(triplet);
					ll cnt1 = count(nums.begin(), nums.end(), triplet[0]);
					ll cnt2 = count(nums.begin(), nums.end(), triplet[1]);
					ll cnt3 = count(nums.begin(), nums.end(), triplet[2]);
					if (triplet[0] != triplet[1] &&
						triplet[0] != triplet[2] &&
						triplet[1] != triplet[2])
						res += cnt1*cnt2*cnt3;
					else if (triplet[0] == triplet[1]
						&& triplet[0] == triplet[2]) {
						ll temp = cnt1*(cnt1 - 1)*(cnt1 - 2);
						res += temp / 6;
					}
					else if (triplet[0] == triplet[1]
						&& triplet[0] != triplet[2]) {
						ll temp = cnt1*(cnt1 - 1);
						res += temp / 2 * cnt3;
					}
					else if (triplet[0] != triplet[1]
						&& triplet[1] == triplet[2]) {
						ll temp = cnt2*(cnt2 - 1);
						res += temp / 2 * cnt1;
					}
					while (front < back
						&& nums[front] == triplet[1]) {
						++front;
						
					}
					while (front < back &&
						nums[back] == triplet[2]) {
						--back;
						
					}
				}
			}
			while (i + 1 < len
				&& nums[i + 1] == nums[i]) {
				++i;
				
			}
		}

		return res % mod;
	}
};
//Runtime: 132 ms, faster than 21.71% of C++ online submissions for 3Sum With Multiplicity.





class Solution {
public:
	int threeSumMulti(vector<int>& nums, int target) {
		const int mod = 1e9 + 7;
		typedef long long ll;
		ll res = 0;
		int len = nums.size();
		sort(nums.begin(), nums.end());
		vector<int> cnt(101, 0);
		for (int i = 0; i < len; ++i) {
			++cnt[nums[i]];
		}
		for (int i = 0; i < len; ++i) {
			int this_target = target - nums[i];
			int front = i + 1;
			int back = len - 1;

			while (front < back) {
				int sum = nums[front] + nums[back];
				if (sum < this_target)
					++front;
				else if (sum > this_target)
					--back;
				else {
					vector<int> triplet(3, 0);
					triplet[0] = nums[i];
					triplet[1] = nums[front];
					triplet[2] = nums[back];
					//res.push_back(triplet);
					ll cnt1 = cnt[triplet[0]];
					ll cnt2 = cnt[triplet[1]];
					ll cnt3 = cnt[triplet[2]];
					if (triplet[0] != triplet[1] &&
						triplet[0] != triplet[2] &&
						triplet[1] != triplet[2])
						res += cnt1*cnt2*cnt3;
					else if (triplet[0] == triplet[1]
						&& triplet[0] == triplet[2]) {
						ll temp = cnt1*(cnt1 - 1)*(cnt1 - 2);
						res += temp / 6;
					}
					else if (triplet[0] == triplet[1]
						&& triplet[0] != triplet[2]) {
						ll temp = cnt1*(cnt1 - 1);
						res += temp / 2 * cnt3;
					}
					else if (triplet[0] != triplet[1]
						&& triplet[1] == triplet[2]) {
						ll temp = cnt2*(cnt2 - 1);
						res += temp / 2 * cnt1;
					}
					while (front < back
						&& nums[front] == triplet[1]) {
						++front;
						
					}
					while (front < back &&
						nums[back] == triplet[2]) {
						--back;
						
					}
				}
			}
			while (i + 1 < len
				&& nums[i + 1] == nums[i]) {
				++i;
				
			}
		}

		return res % mod;
	}
};
//Runtime: 8 ms, faster than 87.92% of C++ online 
//submissions for 3Sum With Multiplicity.