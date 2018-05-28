/*
"输入一个由大写字母‘A-Z’组成的字符串，按照如下方式，对字符串中的字符进行编码：
1.统计每个字符出现的次数，并根据出现次数对字符进行权重分配；
a.出现次数越高，权重越大；
b.出现次数相同，字符值越小，权重越大；
c.权重值为1~26，必须从1开始，连续分配，数值越大，权重越高；
2.把权重最小的两个字符构成二叉树的左右子节点，其和作为根节点（节点值为字符权重）；
a.若两个子节点值不等，较小值作为左子节点；
b.若两个子节点值相同（多字符的权重和与另一个字符权重可能相同），则叶子节点作为左子节点；
3.重复过程2，直到根节点值为所有字符的权重和；
4.将树的左边定位0，右边定位1，从根节点到字符节点的路径，即为其编码值；

示例：
1.输入字符串‘MBCEMAMCBA’，各字符出现次数分别为M:3,A:2,B:2,C:2,E:1；
2.根据字符出现次数和字符大小，进行排序，结果为：M>A>B>C>E，对应权重值为 M:5,A:4,B:3,C:2,E:1
3.根据规则生成权重树：
a.(M:5,A:4,B:3,C:2,E:1)中E:1和C:2值最小，相加得3，则E:1为左节点，C:2为右节点，3为根节点；
b.(M:5,A:4,B:3,3)中B:3和3值最小，相加得6，则B:3为左节点，3为右节点，6为根节点；
c.(M:5,A:4,6)中M:5和A:4值最小，相加得9，则A:4为左节点，M:5为右节点，9为根节点；
d.(6,9)中只有两个值，相加得15，则6为左节点，9为右节点,15为根节点；
e.根节点达到所有字符的权重和1+2+3+4+5=15，结果如下：
15
0/      1\
6         9
0/ 1\     0/ 1\
B:3  3   A:4  M:5
0/ 1\
E:1  C:2"


经过编码后的二进制字符串（使用字符'0'和'1'表示比特位0和1）

1 ≤ T ≤ 10
字符串长度小于等于100

"// 参数：raw_str     输入字符串
// 参数：encoded_str 编码后的字符串
void str_encoding(const std::string& raw_str, std::string& encoded_str)

Input:
1
MBCEMAMCBA

Output:
11000110101110110110010"

其实就是哈弗曼编码
*/

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
#include <cstring>

using namespace::std;

vector<pair<char, string>> vec[256];

struct MinHeapNode {

	// One of the input characters
	char data;

	// Frequency of the character
	unsigned freq;

	// Left and right child
	MinHeapNode *left, *right;

	MinHeapNode(char data, unsigned freq)
		: data(data), freq(freq), left(nullptr), right(nullptr){}
};

// For comparison of
// two heap nodes (needed in min heap)
struct compare {

	bool operator()(MinHeapNode* l, MinHeapNode* r)
	{
		//if (l->freq > r->freq)
		//	return true;
		//else if (l->freq == r->freq)
		//	return l->data < r->data;
		//else
		//	return false;
		return (l->freq > r->freq);
	}
};

// Prints huffman codes from
// the root of Huffman Tree.

void printCodes(MinHeapNode* root, string str)
{

	if (!root)
		return;

	if (root->data != '$') {
		//cout << root->data << ": " << str << "\n";
		vec[root->data].push_back(make_pair(root->data, str));
	}

	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree


void print_queue(priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> q)
{
	while (!q.empty()) {
		std::cout << q.top()->data << " " << q.top()->freq << endl;
		q.pop();
	}
	std::cout << '\n';
}


void HuffmanCodes(char data[], int freq[], int size)
{
	MinHeapNode *left, *right, *top;

	// Create a min heap & inserts all characters of data[]
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

	for (int i = 0; i < size; ++i)
		minHeap.push(new MinHeapNode(data[i], freq[i]));

	//print_queue(minHeap);

	// Iterate while size of heap doesn't become 1
	while (minHeap.size() != 1) {

		// Extract the two minimum
		// freq items from min heap
		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();

		// Create a new internal node with
		// frequency equal to the sum of the
		// two nodes frequencies. Make the
		// two extracted node as left and right children
		// of this new node. Add this node
		// to the min heap '$' is a special value
		// for internal nodes, not used
		top = new MinHeapNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		minHeap.push(top);
	}

	// Print Huffman codes using
	// the Huffman tree built above
	printCodes(minHeap.top(), "");
}

struct letter
{
	char ch;
	int freq;
	letter(char ch, int freq) :ch(ch), freq(freq){}
	letter() {}
	bool operator<(const letter &oters) const
	{
		if (freq < oters.freq)
			return true;
		else if (freq == oters.freq)
			return ch > oters.ch;
		else
			return false;
	}

	bool operator>(const letter &oters) const
	{
		if (freq > oters.freq)
			return true;
		else if (freq == oters.freq)
			return ch < oters.ch;
		else
			return false;
	}
};

void test1()
{
	//freopen("input.txt", "r", stdin);
	int t;
	cin >> t;
	while (t--) {
		for (int i = 0; i < 256; ++i)
			vec[i].clear();
		string s;
		cin >> s;
		vector<char> charVec;
		vector<int> freq;
		int hashTable[256];
		memset(hashTable, 0, sizeof(hashTable));
		for (int i = 0; i < s.length(); ++i)
			++hashTable[s[i]];

		string str = s;
		sort(str.begin(), str.end());
		auto last = unique(str.begin(), str.end());
		str.erase(last, str.end());
		for (int i = 0; i < str.length(); ++i)
			charVec.push_back(str[i]);
		for (int i = 0; i < 256; ++i)
			if (hashTable[i] > 0)
				freq.push_back(hashTable[i]);
		vector<letter> vecLet(freq.size());
		for (int i = 0; i < freq.size(); ++i) {
			vecLet[i].ch = charVec[i];
			vecLet[i].freq = freq[i];
			//cout << charVec[i] << ' ' << freq[i] << endl;
		}

		sort(vecLet.begin(), vecLet.end(), greater<letter>());
		for (int i = 0, j = vecLet.size(); i < vecLet.size(); ++i)
			vecLet[i].freq = j--;
		for (int i = 0; i < vecLet.size(); ++i) {
			charVec[i] = vecLet[i].ch;
			freq[i] = vecLet[i].freq;
		}

		/*for (int i = 0; i < freq.size(); ++i)
		cout << charVec[i] << ' ' << freq[i] << endl;*/


		HuffmanCodes(charVec.data(), freq.data(), freq.size());

		for (int i = 0; i < s.size(); ++i)
			cout << vec[s[i]][0].second.c_str();
		cout << endl;
	}
}

int main()
{
	test1();

	return 0;
}

