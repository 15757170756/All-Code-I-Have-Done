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

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2) {
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
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