/*
28. Implement strStr()
DescriptionHintsSubmissionsDiscussSolution
Implement strStr().

Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:

Input: haystack = "hello", needle = "ll"
Output: 2
Example 2:

Input: haystack = "aaaaa", needle = "bba"
Output: -1
Clarification:

What should we return when needle is an empty string? This is a great question to ask during an interview.

For the purpose of this problem, we will return 0 when needle is an empty string. This is consistent to C's strstr() and Java's indexOf().

Seen this question in a real interview before?  

*/

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.size() == 0)
			return 0;
		return (haystack.find(needle));
    }
};

//Submission Result: Accepted