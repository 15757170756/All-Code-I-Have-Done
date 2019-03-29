/*
https://leetcode.com/problems/wildcard-matching/

44. Wildcard Matching
Hard

853

63

Favorite

Share
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like ? or *.
Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.
Example 3:

Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
Example 4:

Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
Example 5:

Input:
s = "acdcb"
p = "a*c?b"
Output: false
Accepted
158,115
Submissions
711,495
Seen this question in a real interview before?
*/


/*
The basic idea is to have one pointer for the string and one pointer for the pattern. This algorithm iterates at most length(string) + length(pattern) times, for each iteration, at least one pointer advance one step.


*/
bool isMatch(char* s, char* p) 
{
	char *star = NULL;
	char *ss = s;
	while (*s) {
		if ((*p == '?') || (*p == *s)) {
			++s; ++p;
			continue;
		}
		if (*p == '*') {
			star = p++; ss = s;
			continue;
		}
		if (star) {
			p = star + 1; s = ++ss;
			continue;
		}
		return false;
	}
	while (*p == '*')
		p++;

	return !*p;
}

/*
Success
Details 
Runtime: 12 ms, faster than 100.00% of 
C online submissions for Wildcard Matching.
*/


//or
bool isMatch(char* s, char* p) 
{
	char *star = NULL;
	char *ss = s;
	while (*s) {
		if ((*p == '?') || (*p == *s)) {
			++s;
			++p;
		}
		else if (*p == '*') {
			ss = s;
			star = p++; 
		}
		else if (star) {
			s = ++ss;
			p = star + 1; 
		}
		else 
            return false;
	}
	while (*p == '*')
		p++;

	return !*p;
}