/*
We are given two sentences A and B.  (A sentence is a string of space separated words.  Each word consists only of lowercase letters.)

A word is uncommon if it appears exactly once in one of the sentences, and does not appear in the other sentence.

Return a list of all uncommon words. 

You may return the list in any order.

 

Example 1:

Input: A = "this apple is sweet", B = "this apple is sour"
Output: ["sweet","sour"]
Example 2:

Input: A = "apple apple", B = "banana"
Output: ["banana"]
 

Note:

0 <= A.length <= 200
0 <= B.length <= 200
A and B both contain only spaces and lowercase letters.
*/

class Solution {
public:
	void split(const string &str, const char delim,
		vector<string> &resultStr)
	{
		istringstream ss(str);
		string item;
		while (getline(ss, item, delim))
			if (item.length() > 0)
				resultStr.push_back(item);
	}
	vector<string> uncommonFromSentences(string A, string B) {
		vector<string> vecStrA, vecStrB;
		split(A, ' ', vecStrA);
		split(B, ' ', vecStrB);
		vector<string> result;
		for (int i = 0; i < vecStrA.size(); ++i) {
			bool isCon = false;
			for (int j = 0; j < vecStrA.size(); ++j) {
				if (vecStrA[i] == vecStrA[j] && i != j) {
					isCon = true;
					break;
				}
			}
			for (int j = 0; j < vecStrB.size(); ++j) {
				if (vecStrA[i] == vecStrB[j]) {
					isCon = true;
					break;
				}
			}
			if(!isCon)
				result.push_back(vecStrA[i]);
		}

		for (int i = 0; i < vecStrB.size(); ++i) {
			bool isCon = false;
			for (int j = 0; j < vecStrB.size(); ++j) {
				if (vecStrB[i] == vecStrB[j] && i != j) {
					isCon = true;
					break;
				}
			}
			for (int j = 0; j < vecStrA.size(); ++j) {
				if (vecStrB[i] == vecStrA[j]) {
					isCon = true;
					break;
				}
			}
			if (!isCon)
				result.push_back(vecStrB[i]);
		}
		return result;
	}
};