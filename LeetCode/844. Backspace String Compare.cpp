/*

844. Backspace String Compare
DescriptionHintsSubmissionsDiscussSolution
Given two strings S and T, return if they 
are equal when both are typed into
 empty text editors. # means a backspace character.

 

Example 1:

Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
Example 2:

Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
Example 3:

Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
Example 4:

Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
 

Note:

1 <= S.length <= 200
1 <= T.length <= 200
S and T only contain lowercase letters and '#' characters.
Seen this question in a real interview before?  

*/


class Solution {
public:
	bool backspaceCompare(string S, string T) {
		for (int i = 0; i < S.size();) {
			if (S[i] == '#' && i != 0) {
				S.erase(S.begin() + i);
				S.erase(S.begin() + i - 1);
				i = 0;
			}
			else if (S[i] == '#' && i == 0) {
				S.erase(S.begin());
			}
			else
				++i;
		}
		for (int i = 0; i < T.size();) {
			if (T[i] == '#' && i != 0) {
				T.erase(T.begin() + i);
				T.erase(T.begin() + i - 1);
				i = 0;
			}
			else if (T[i] == '#' && i == 0) {
				T.erase(T.begin());
			}
			else
				++i;
		}
		return S == T;
	}
};

//Submission Result: Accepted 
