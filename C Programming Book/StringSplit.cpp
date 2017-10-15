#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace::std;

vector<string> split(const string &s, char delim)
{
	vector<string> elems;
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
		if (item.length() > 0)
			elems.push_back(item);

	return elems;
}

int main()
{
	string s = "I am lichaofeng, nice to meet you";
	vector<string> result = split(s, ' ');
	for (int i = 0; i < result.size(); ++i)
		cout << result[i];

	return 0;
}