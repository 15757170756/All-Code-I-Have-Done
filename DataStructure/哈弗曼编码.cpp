//#include <iostream>
//#include <vector>
//#include <string>
//#include <algorithm>
//#include <fstream>
//#include <cassert>
//#include <list>
//#include <queue>
//#include <limits>
//#include <unordered_set>
//#include <sstream>
//#include <map>
//#include <iterator>
//#include <set>
//#include <stack>
//#include <deque>
//#include <functional>
//#include <cstdlib>
//#include <ctime>
//#include <numeric>
//#include <unordered_map>
//
//using namespace::std;
//
//struct MinHeapNode {
//
//	// One of the input characters
//	char data;
//
//	// Frequency of the character
//	unsigned freq;
//
//	// Left and right child
//	MinHeapNode *left, *right;
//
//	MinHeapNode(char data, unsigned freq) 
//		: data(data), freq(freq), left(nullptr), right(nullptr){}
//};
//
//// For comparison of
//// two heap nodes (needed in min heap)
//struct compare {
//
//	bool operator()(MinHeapNode* l, MinHeapNode* r)
//	{
//		//if (l->freq > r->freq)
//		//	return true;
//		//else if (l->freq == r->freq)
//		//	return l->data < r->data;
//		//else
//		//	return false;
//		return (l->freq > r->freq);
//	}
//};
//
//// Prints huffman codes from
//// the root of Huffman Tree.
//vector<pair<char, string>> vec[256];
//void printCodes(struct MinHeapNode* root, string str)
//{
//
//	if (!root)
//		return;
//
//	if (root->data != '$') {
//		//cout << root->data << ": " << str << "\n";
//		vec[root->data].push_back(make_pair(root->data, str));
//	}
//
//	printCodes(root->left, str + "0");
//	printCodes(root->right, str + "1");
//}
//
//// The main function that builds a Huffman Tree and
//// print codes by traversing the built Huffman Tree
//
//
//void print_queue(priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> q) 
//{
//	while (!q.empty()) {
//		std::cout << q.top()->data << " " << q.top()->freq << endl;
//		q.pop();
//	}
//	std::cout << '\n';
//}
//
//
//void HuffmanCodes(char data[], int freq[], int size)
//{
//	MinHeapNode *left, *right, *top;
//
//	// Create a min heap & inserts all characters of data[]
//	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
//
//	for (int i = 0; i < size; ++i)
//		minHeap.push(new MinHeapNode(data[i], freq[i]));
//
//	print_queue(minHeap);
//
//	// Iterate while size of heap doesn't become 1
//	while (minHeap.size() != 1) {
//
//		// Extract the two minimum
//		// freq items from min heap
//		left = minHeap.top();
//		minHeap.pop();
//
//		right = minHeap.top();
//		minHeap.pop();
//
//		// Create a new internal node with
//		// frequency equal to the sum of the
//		// two nodes frequencies. Make the
//		// two extracted node as left and right children
//		// of this new node. Add this node
//		// to the min heap '$' is a special value
//		// for internal nodes, not used
//		top = new MinHeapNode('$', left->freq + right->freq);
//
//		top->left = left;
//		top->right = right;
//
//		minHeap.push(top);
//	}
//
//	// Print Huffman codes using
//	// the Huffman tree built above
//	printCodes(minHeap.top(), "");
//}
//
//struct letter
//{
//	char ch;
//	int freq;
//	letter(char ch, int freq) :ch(ch), freq(freq){}
//	letter() {}
//	bool operator<(const letter &oters) const
//	{
//		if (freq < oters.freq)
//			return true;
//		else if (freq == oters.freq)
//			return ch < oters.ch;
//		else
//			return false;
//	}
//
//	bool operator>(const letter &oters) const
//	{
//		if (freq > oters.freq)
//			return true;
//		else if (freq == oters.freq)
//			return ch < oters.ch;
//		else
//			return false;
//	}
//};
//
//void test1()
//{
//	freopen("input.txt", "r", stdin);
//	int t;
//	cin >> t;
//	while (t--) {
//		for (int i = 0; i < 256; ++i)
//			vec[i].clear();
//		string s;
//		cin >> s;
//		vector<char> charVec;
//		vector<int> freq;
//		int hashTable[256];
//		memset(hashTable, 0, sizeof(hashTable));
//		for (int i = 0; i < s.length(); ++i)
//			++hashTable[s[i]];
//
//		string str = s;
//		sort(str.begin(), str.end());
//		auto last = unique(str.begin(), str.end());
//		str.erase(last, str.end());
//		for (int i = 0; i < str.length(); ++i)
//			charVec.push_back(str[i]);
//		for (int i = 0; i < 256; ++i)
//			if (hashTable[i] > 0) 
//				freq.push_back(hashTable[i]);
//		vector<letter> vecLet(freq.size());
//		for (int i = 0; i < freq.size(); ++i) {
//			vecLet[i].ch = charVec[i];
//			vecLet[i].freq = freq[i];
//			cout << charVec[i] << ' ' << freq[i] << endl;
//		}
//
//		sort(vecLet.begin(), vecLet.end(), greater<letter>());
//		for (int i = 0, j = vecLet.size(); i < vecLet.size(); ++i) 
//			vecLet[i].freq = j--;
//		for (int i = 0; i < vecLet.size(); ++i) {
//			charVec[i] = vecLet[i].ch;
//			freq[i] = vecLet[i].freq;
//		}
//
//		for (int i = 0; i < freq.size(); ++i) 
//			cout << charVec[i] << ' ' << freq[i] << endl;
//		
//
//		HuffmanCodes(charVec.data(), freq.data(), freq.size());
//
//		for (int i = 0; i < s.size(); ++i)
//			cout << vec[s[i]][0].second;
//		cout << endl;
//	}
//}
//
//int main()
//{
//	test1();
//
//	return 0;
//}



// C++ program for Huffman Coding
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

using namespace std;

// A Huffman tree node
struct MinHeapNode {

	// One of the input characters
	char data;

	// Frequency of the character
	unsigned freq;

	// Left and right child
	MinHeapNode *left, *right;

	MinHeapNode(char data, unsigned freq)

	{

		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

// For comparison of
// two heap nodes (needed in min heap)
struct compare {

	bool operator()(MinHeapNode* l, MinHeapNode* r)

	{
		return (l->freq > r->freq);
	}
};

// Prints huffman codes from
// the root of Huffman Tree.
void printCodes(struct MinHeapNode* root, string str)
{

	if (!root)
		return;

	if (root->data != '$')
		cout << root->data << ": " << str << "\n";

	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size)
{
	struct MinHeapNode *left, *right, *top;

	// Create a min heap & inserts all characters of data[]
	priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

	for (int i = 0; i < size; ++i)
		minHeap.push(new MinHeapNode(data[i], freq[i]));

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

// Driver program to test above functions
int main()
{

	char arr[] = { 'a', 'b', 'c', 'd', 'e', 'r' };
	int freq[] = { 3, 6, 5, 4, 2, 1 };

	int size = sizeof(arr) / sizeof(arr[0]);

	HuffmanCodes(arr, freq, size);

	return 0;
}

/*
output£º
d: 00
c: 01
b: 10
a: 110
r: 1110
e: 1111
*/
