/*
842. Split Array into Fibonacci Sequence
DescriptionHintsSubmissionsDiscussSolution
Given a string S of digits, such as S = "123456579",
 we can split it into a Fibonacci-like sequence [123, 456, 579].

Formally, a Fibonacci-like sequence is a list F of non-negative integers such that:

0 <= F[i] <= 2^31 - 1, (that is, each integer fits a 32-bit signed integer type);
F.length >= 3;
and F[i] + F[i+1] = F[i+2] for all 0 <= i < F.length - 2.
Also, note that when splitting the string into pieces, 
each piece must not have extra leading zeroes, except if the piece is the number 0 itself.

Return any Fibonacci-like sequence split from S, or return [] if it cannot be done.

Example 1:

Input: "123456579"
Output: [123,456,579]
Example 2:

Input: "11235813"
Output: [1,1,2,3,5,8,13]
Example 3:

Input: "112358130"
Output: []
Explanation: The task is impossible.
Example 4:

Input: "0123"
Output: []
Explanation: Leading zeroes are not allowed, so "01", "2", "3" is not valid.
Example 5:

Input: "1101111"
Output: [110, 1, 111]
Explanation: The output [11, 0, 11, 11] would also be accepted.
Note:

1 <= S.length <= 200
S contains only digits.
Seen this question in a real interview before?  

*/



/*
solution:
4ms backtracking in C++
14
VIEWS
0
Created at: 21 hours ago

ttsugrii
ttsugrii
 3
Trying out all partitions of input text is
 bound to exceed a limit for any large input due 
 to exponential complexity of the problem. 
 Fortunately, most of the partitions violate
  one of the invariants very early on.
  For example, as soon as partition encounters 
  an element that is not a sum of the previous two elements, 
  it cannot possibly be a part of the solution. 
  Similarly it makes no sense to explore partitions
 that include an element starting with 0 but not 0. 
 Having these checks greatly limits the number of 
 possible partitions and result in a fairly fast solution:
*/

class Solution {
private:
    bool canSplit(const string& s, int idx, vector<int>& state) const {
        if (idx == s.size() && state.size() >= 3) 
        	return true; // F.length >= 3
        long num = 0;
        for (int i = idx; i < s.size(); ++i) {
            if (i != idx && s[idx] == '0') 
            	return false; // each piece must not have extra leading zeroes
            num = num * 10 + (s[i] - '0');
            if (num > numeric_limits<int>::max()) 
            	return false; // 0 <= F[i] <= 2^31 - 1
            if (state.size() >= 2 
            	&& (state[state.size()-2] + state.back() != num)) 
            	continue; // F[i] + F[i+1] = F[i+2]
            state.push_back(num);
            if (canSplit(s, i+1, state)) 
            	return true;
            state.pop_back();
        }
        return false;
    }
public:
    vector<int> splitIntoFibonacci(const string& S) {
        vector<int> state;
        if (canSplit(S, 0, state)) 
        	return state;
        return {};
    }
};