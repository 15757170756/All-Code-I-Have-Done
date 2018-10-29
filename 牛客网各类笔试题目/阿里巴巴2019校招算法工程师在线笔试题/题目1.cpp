/*
只需开口说话就能控制计算机做自己想做的事情，
这种新奇的人机交互方式已经从科幻小说进入了现实世界。
那么机器是如何理解人说的话的呢？这是一个复杂的过程，
其中一个重要的任务就是要教会机器理解话语中的重点，即关键词。
比如对机器说“请播放周杰伦的青花瓷”，机器要能理解 “周杰伦”是一个歌手，
而“青花瓷”是一首歌曲。而我们知道，“周杰”也是一个歌手，
那机器如何抉择呢？为了简化问题，
我们使用从左到右的最大长度匹配的原则：在本句里面，“周杰”的字符串长度比“周杰伦”小，
所以识别“周杰伦“作为歌手。

通过互联网，我们能收集到一个庞大的知识库，帮助我们教机器来做这件事情。
知识库中有所有的歌曲的列表，所有的歌手的列表，以及其他各种实体的列表。
那么怎么使用这些实体通过上面的规则来教会机器识别关键词呢？

编译器版本: gcc 4.8.4
请使用标准输入输出(stdin，stdout) ；请把所有程序写在一个文件里，勿使用已禁用图形、文件、网络、系统相关的头文件和操作，如sys/stat.h , unistd.h , curl/curl.h , process.h
时间限制: 3S (C/C++以外的语言为: 5 S)   内存限制: 128M (C/C++以外的语言为: 640 M)
输入:
输入数据包含两行，
第一行，实体列表，多种实体之间用分号隔开，实体名和实体值之间用下划线隔开，多个实体值之间用竖线隔开，所有标点都是英文状态下的，格式如下：
实体名称1_实体值1|实体值2|…;实体名称2_实体值1|实体值2|…;… 
第二行，用户的自然语言指令
输出:
被标记了关键词的指令。指令中的关键词前后加一个空格被单独分出来，
并在后面跟上"/"+实体名称来标记。如果一个实体值属于多个实体，
将这些实体都标记出来，并按照实体名称的字符串顺序正序排列，并以逗号分隔。
输入范例:
singer_周杰|周杰伦|刘德华|王力宏;song_冰雨|北京欢迎你|七里香;actor_周杰伦|孙俪
请播放周杰伦的七里香给我听
输出范例:
请播放 周杰伦/actor,singer 的 七里香/song 给我听
*/



#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

void split(const string &s, const char delim, vector<string> &resultStr)
{
	istringstream ss(s);
	string item;
	while (getline(ss, item, delim))
		if (item.length() > 0)
			resultStr.push_back(item);
}

int main(int argc, char* argv[])
{
	//freopen("input.txt", "r", stdin);
	string s1, s2;
	cin >> s1;
	cin >> s2;
	vector<string> ssa;
	split(s1, ';', ssa);
	vector<vector<string>> ssvec(ssa.size());
	for (int i = 0; i < ssa.size(); ++i) {
		vector<string> temp;
		string stemp = ssa[i];
		auto idx = stemp.find('_');
		ssvec[i].push_back(stemp.substr(0, idx));
		split(stemp.substr(idx + 1), '|', temp);
		for (int j = 0; j < temp.size(); ++j)
			ssvec[i].push_back(temp[j]);
	}

	vector<pair<int, int>> pairInt;
	vector<int> 
	for (int i = 0; i < ssvec.size(); ++i) {
		for (int j = 0; j < ssvec[i].size(); ++j) {
			//cout << ssvec[i][j] << ' ';
			string &temp = ssvec[i][j];
			int idx = s2.find(temp);
			if (idx != string::npos) {
				pairInt.emplace_back(i, j);
			}
		}
	}
	string actor;
	string song;
	for (int i = 0; i < pairInt.size(); ++i) {
		for (int j = i+1; j < pairInt.size(); ++j) {
			if (pairInt[i].first == pairInt[j].first) {
				int x1 = pairInt[i].first;
				int y1 = pairInt[i].second;
				int x2 = pairInt[j].first;
				int y2 = pairInt[j].second;
				actor = (ssvec[x1][y1].size() > ssvec[x2][y2].size() ?
					ssvec[x1][y1] : ssvec[x2][y2]);
			}
		}
	}

	vector<string> id;
	for (int i = 0; i < ssvec.size(); ++i) {
		for (int j = 0; j < ssvec[i].size(); ++j) {
			if (ssvec[i][j] == actor)
				id.push_back(ssvec[i][0]);
		}
	}
	sort(id.begin(), id.end());
	cout << "请播放 " << actor << "/";
	for (int i = 0; i < id.size(); ++i) {
		if (i != id.size() - 1)
			cout << id[i] << ',';
		else
			cout << id[i] << ' ';
	}
	cout << "的 ";
	cout << song << "/" <<"song" << " 给我听" << endl;
	return 0;
}
