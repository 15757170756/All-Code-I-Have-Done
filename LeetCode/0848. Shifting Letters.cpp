/*
848. Shifting Letters
DescriptionHintsSubmissionsDiscussSolution
We have a string S of lowercase letters, and an integer array shifts.

Call the shift of a letter, the next letter in the alphabet, (wrapping around so that 'z' becomes 'a'). 

For example, shift('a') = 'b', shift('t') = 'u', and shift('z') = 'a'.

Now for each shifts[i] = x, we want to shift the first i+1 letters of S, x times.

Return the final string after all such shifts to S are applied.

Example 1:

Input: S = "abc", shifts = [3,5,9]
Output: "rpl"
Explanation: 
We start with "abc".
After shifting the first 1 letters of S by 3, we have "dbc".
After shifting the first 2 letters of S by 5, we have "igc".
After shifting the first 3 letters of S by 9, we have "rpl", the answer.
Note:

1 <= S.length = shifts.length <= 20000
0 <= shifts[i] <= 10 ^ 9
Seen this question in a real interview before?  
Difficulty:Medium
Total Accepted:1.9K
Total Submissions:6.1K
Contributor:awice
Subscribe to see which companies asked this question.

Related Topics 


*/


class Solution {
public:
    string shiftingLetters(string S, vector<int>& shifts) {
        int sum = 0;
        for(auto riter = shifts.rbegin(); 
            riter != shifts.rend(); ++riter){
            *riter = ((*riter % 26) + (sum % 26))%26;
            sum = *riter;
        }
        
        for(auto i = 0; i < S.size(); ++i){
            S[i] = (((S[i] - 'a') + shifts[i]) % 26) + 'a';
        }
        return S;
    }
};