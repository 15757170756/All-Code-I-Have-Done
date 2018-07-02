/*
67. Add Binary
DescriptionHintsSubmissionsDiscussSolution
Given two binary strings, return their sum (also a binary string).

The input strings are both non-empty and contains only characters 1 or 0.

Example 1:

Input: a = "11", b = "1"
Output: "100"
Example 2:

Input: a = "1010", b = "1011"
Output: "10101"

*/



class Solution {
public:
	string addBinary(string a, string b) {
		int size1 = a.size();
		int size2 = b.size();
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		if (size1 > size2) {
			for (int i = 0; i < size1 - size2; ++i)
				b.push_back('0');
		}
		else if(size2 > size1) {
			for (int i = 0; i < size2 - size1; ++i)
				a.push_back('0');
		}
		char result[1000];
		int jinwei = 0;
		int i;
		int len = max(size1, size2);
		for (i = 0; i < len; ++i) {
			int temp = (a[i] - '0') + (b[i] - '0') + jinwei;
			if (temp > 1) {
				jinwei = 1;
				temp = temp % 2;
			}
			else
				jinwei = 0;
			result[i] = temp + '0';
		}
		if (jinwei == 1) {
			result[i] = '1';
			result[i + 1] = '\0';
		}
		else
			result[i] = '\0';
	
		string str(result);
		reverse(str.begin(), str.end());
		return str;
	}
};

//Submission Result: Accepted 







std::string addBinary(std::string a, std::string b) 
{
    std::string result;
    int sum = 0;

    int i = a.length() - 1;
    int j = b.length() - 1;
    while ((i >= 0) || (j >= 0) || (sum == 1)) {
        sum += ((i >= 0) ? a[i] - '0' : 0);
        sum += ((j >= 0) ? b[j] - '0' : 0);
        result = char((sum % 2) + '0') + result;
        sum /= 2;
        i--; j--;
    }

    return result;
}



class Solution:
    def addBinary(self, a, b):
        return bin(eval('0b' + a) + eval('0b' + b))[2:]