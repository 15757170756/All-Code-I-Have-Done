#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>
#include <vector>
#include <functional>
#include <string>
#include <cstdio>
#include <sstream>
#include <algorithm>


using namespace std;


string getFileName(string path)
{
	int pos = path.rfind("\\");
	return path.substr(pos + 1);
}

string modifyName(string name)
{
	if (name.size() > 16)
		name = name.substr(name.size() - 16);
	return name;
}

struct ErrRecord
{
	string file;
	int lineNo;
	int count;

	ErrRecord(string file, int lineNo)
	{
		this->file = file;
		this->lineNo = lineNo;
		count = 1;
	}

	bool operator==(const ErrRecord& a)
	{
		return (file == a.file) && (lineNo == a.lineNo);
	}
};

int main()
{
	freopen("input.txt", "r", stdin);
	string file;
	int lineNo;
	vector<ErrRecord> vec;
	while (cin >> file >> lineNo) {
		ErrRecord record(getFileName(file), lineNo);
		vector<ErrRecord>::iterator res = find(vec.begin(), vec.end(), record);
		if (res == vec.end())
			vec.emplace_back(record);
		else
			res->count++;
	}

	int cnt = 0;
	for (ErrRecord& item : vec) {
		if (cnt + 8 >= vec.size()) {
			cout << modifyName(item.file) << ' ' <<
				item.lineNo << ' ' << item.count << endl;
		}
		++cnt;
	}
	
	return 0;
}


