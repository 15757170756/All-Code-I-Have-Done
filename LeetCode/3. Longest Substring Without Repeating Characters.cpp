/*
3. Longest Substring Without Repeating Characters
DescriptionHintsSubmissionsDiscussSolution
Given a string, find the length of the longest
 substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. 
Note that the answer must be a substring, 
"pwke" is a subsequence and not a substring.

Seen this question in a real interview before?  
*/









class Solution {
public:
    int lengthOfLongestSubstring(string s) {
      int kInitPos = -1;
        std::vector<int> hashmap(256, kInitPos);
        int low = 0;
        int maxlen = 0;
        for (int i = 0; i != s.size(); ++i) {
            int key = s[i];
            if (hashmap[key] != kInitPos && hashmap[key] >= low) {
                maxlen = std::max(maxlen, i - low);
                low = hashmap[key] + 1;
            }
            hashmap[key] = i;
        }
        return std::max(maxlen, (int)(s.size() - low));
    }
};

//Submission Result: Accepted 