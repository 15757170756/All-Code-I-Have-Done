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







#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <list>
#include <queue>
#include <limits>
#include <unordered_set>
#include <sstream>
#include <map>
#include <iterator>
#include <set>
#include <stack>
#include <deque>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <unordered_map>

using namespace::std;

int lengthOfLongestSubstring(string s) {
    set<char> norep;
    int ans = 0;
    for (int i = 0, j = 0; i < s.size();){
        //如果字符不存在，插入到set中
        if (norep.count(s[i]) == 0)
            norep.insert(norep.end(), s[i++]);
        //set是有序的，我们想从头开始删除字符，按着s的顺序删除，而不是set的顺序。
        else 
            norep.erase(s[j++]);
        ans = max(ans, int(norep.size()));
    }
    return ans;
}

int longest_unique_substr_len(const std::string& s)
{
    int kInitPos = -1;
    std::vector<int> hashmap(26, kInitPos);
    int low = 0;
    int maxlen = 0;
    for (int i = 0; i != s.size(); ++i) {
        int key = s[i] - 'a';
        if (hashmap[key] != kInitPos && hashmap[key] >= low) {
            maxlen = std::max(maxlen, i - low);
            low = hashmap[key] + 1;
        }
        hashmap[key] = i;
    }
    return std::max(maxlen, (int)(s.size() - low));
}

void test1()
{
    //freopen("input.txt", "r", stdin);
    int t;
    cin >> t;
    while (t--) {
        string str;
        cin >> str;
        cout << lengthOfLongestSubstring(str) << endl;
    }

}


int main(int argc, char* argv[])
{
    test1();
    return 0;
}