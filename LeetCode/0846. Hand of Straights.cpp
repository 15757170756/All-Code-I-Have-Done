/*
846. Hand of Straights
User Accepted: 586
User Tried: 712
Total Accepted: 590
Total Submissions: 1322
Difficulty: Medium
Alice has a hand of cards, given as an array of integers.

Now she wants to rearrange the cards into groups so that each group is size W, 
and consists of W consecutive cards.

Return true if and only if she can.

 

Example 1:198. House Robber
DescriptionHintsSubmissionsDiscussSolution
You are a professional robber planning to rob houses along a street.
 Each house has a certain amount of money stashed, 
 the only constraint stopping you from robbing each of them 
 is that adjacent houses have security system connected 
 and it will automatically contact the police
  if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the
 amount of money of each house, 
 determine the maximum amount of money you can rob tonight without alerting the police.

Example 1:

Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.
Example 2:

Input: [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
             Total amount you can rob = 2 + 9 + 1 = 12.
Seen this question in a real interview before?  


Input: hand = [1,2,3,6,2,3,4,7,8], W = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8].
Example 2:

Input: hand = [1,2,3,4,5], W = 4
Output: false
Explanation: Alice's hand can't be rearranged into groups of 4.
 

Note:

1 <= hand.length <= 10000
0 <= hand[i] <= 10^9
1 <= W <= hand.length
*/