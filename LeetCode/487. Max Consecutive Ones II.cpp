/*
Given a binary array, find the maximum number of consecutive 1s in this array 
if you can flip at most one 0.

Example 1:

Input: [1,0,1,1,0]
Output: 4
Explanation: Flip the first zero will get the the maximum number of consecutive 1s.
    After flipping, the maximum number of consecutive 1s is 4.
 

Note:

The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000
 

Follow up:
What if the input numbers come in one by one as an infinite stream? 
In other words, you can't store all numbers coming 
from the stream as it's too large to hold in memory. 
Could you solve it efficiently?


https://www.cnblogs.com/grandyang/p/6376115.html
*/

/*
这道题在之前那道题Max Consecutive Ones的基础上加了一个条件，
说我们有一次将0翻转成1的机会，问此时最大连续1的个数，
再看看follow up中的说明，很明显是让我们只遍历一次数组，
那我们想，肯定需要用一个变量cnt来记录连续1的个数吧，
那么当遇到了0的时候怎么处理呢，因为我们有一次0变1的机会，
所以我们遇到0了还是要累加cnt，
然后我们此时需要用另外一个变量cur来保存当前cnt的值，
然后cnt重置为0，以便于让cnt一直用来统计纯连续1的个数，
然后我们每次都用用cnt+cur来更新结果res，参见代码如下：
*/
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int res = 0, cur = 0, cnt = 0;
        for (int num : nums) {
            ++cnt;
            if (num == 0) {
                cur = cnt;
                cnt = 0;
            } 
            res = max(res, cnt + cur);
        }
        return res;
    }
};









//能翻转k次
/*
上面的方法有局限性，如果题目中说能翻转k次怎么办呢，
我们最好用一个通解来处理这类问题。
我们可以维护一个窗口[left,right]来容纳至少k个0。我们遇到了0，
就累加zero的个数，然后判断如果此时0的个数大于k，
那么我们我们右移左边界left，如果移除掉的nums[left]为0，
那么我们zero自减1。如果不大于k，
那么我们用窗口中数字的个数来更新res，参见代码如下：
input: 1001010101 2
output: 5
*/
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums, int k) {
        int res = 0, zero = 0, left = 0;
        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] == 0) 
            	++zero;
            while (zero > k) {
                if (nums[left++] == 0) 
                	--zero;
            }
            res = max(res, right - left + 1);
        }
        return res;
    }
};


//input: 1001010101 2
//output: 5
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums, int k) {
        int res = 0, left = 0;
        queue<int> q;
        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] == 0) 
            	q.push(right);
            if (q.size() > k) {
                left = q.front() + 1; 
                q.pop();
            }
            res = max(res, right - left + 1);
        }
        return res;
    }
};