/*
Given a string S, return the "reversed" string where all characters that are not a letter stay in the same place, and all letters reverse their positions.

 

Example 1:

Input: "ab-cd"
Output: "dc-ba"
Example 2:

Input: "a-bC-dEf-ghIj"
Output: "j-Ih-gfE-dCba"
Example 3:

Input: "Test1ng-Leet=code-Q!"
Output: "Qedo1ct-eeLg=ntse-T!"
 

Note:

S.length <= 100
33 <= S[i].ASCIIcode <= 122 
S doesn't contain \ or "
*/

class Solution {
public:
	string reverseOnlyLetters(string S) {
		int len = S.size();
		string s_new;
		vector<int> idxes;
		for (int i = 0; i < len; ++i) {
			if (isupper(S[i]) || islower(S[i]))
				s_new.push_back(S[i]);
			else
				idxes.push_back(i);
		}
		reverse(s_new.begin(), s_new.end());
		auto sta = S.begin();
		for (int i = 0; i < idxes.size(); ++i) {
			s_new.insert(idxes[i], 1, S[idxes[i]]);
		}
		return s_new;
	}
};