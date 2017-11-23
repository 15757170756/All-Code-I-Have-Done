#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace::std;

void split(const string &s, const char delim, vector<string> &resultStr)
{
	istringstream ss(s);
	string item;
	while (getline(ss, item, delim))
		if (item.length() > 0)
			resultStr.push_back(item);
}

int main()
{
	string s = "I am lichaofeng, nice to meet you";
	vector<string> result;
	split(s, ' ', result);
	for (int i = 0; i < result.size(); ++i)
		cout << result[i];

	return 0;
}