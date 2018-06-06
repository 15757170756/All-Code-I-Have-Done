/*
Eight
Time Limit: 10000/5000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)
Total Submission(s): 29566    Accepted Submission(s): 7746
Special Judge

Problem Description
The 15-puzzle has been around for over 100 years; even if you don't know it by that name, you've seen it. It is constructed with 15 sliding tiles, each with a number from 1 to 15 on it, and all packed into a 4 by 4 frame with one tile missing. Let's call the missing tile 'x'; the object of the puzzle is to arrange the tiles so that they are ordered as: 

 1  2  3  4
 5  6  7  8
 9 10 11 12
13 14 15  x

where the only legal operation is to exchange 'x' with one of the tiles with which it shares an edge. As an example, the following sequence of moves solves a slightly scrambled puzzle: 

 1  2  3  4     1  2  3  4     1  2  3  4     1  2  3  4
 5  6  7  8     5  6  7  8     5  6  7  8     5  6  7  8
 9  x 10 12     9 10  x 12     9 10 11 12     9 10 11 12
13 14 11 15    13 14 11 15    13 14  x 15    13 14 15  x
            r->            d->            r->

The letters in the previous row indicate which neighbor of the 'x' tile is swapped with the 'x' tile at each step; legal values are 'r','l','u' and 'd', for right, left, up, and down, respectively. 

Not all puzzles can be solved; in 1870, a man named Sam Loyd was famous for distributing an unsolvable version of the puzzle, and 
frustrating many people. In fact, all you have to do to make a regular puzzle into an unsolvable one is to swap two tiles (not counting the missing 'x' tile, of course). 

In this problem, you will write a program for solving the less well-known 8-puzzle, composed of tiles on a three by three 
arrangement.
 

Input
You will receive, several descriptions of configuration of the 8 puzzle. One description is just a list of the tiles in their initial positions, with the rows listed from top to bottom, and the tiles listed from left to right within a row, where the tiles are represented by numbers 1 to 8, plus 'x'. For example, this puzzle 

1 2 3 
x 4 6 
7 5 8 

is described by this list: 

1 2 3 x 4 6 7 5 8
 

Output
You will print to standard output either the word ``unsolvable'', if the puzzle has no solution, or a string consisting entirely of the letters 'r', 'l', 'u' and 'd' that describes a series of moves that produce a solution. The string should include no spaces and start at the beginning of the line. Do not print a blank line between cases.
 

Sample Input
2  3  4  1  5  x  7  6  8
 

Sample Output
ullddrurdllurdruldr
 

Source
South Central USA 1998 (Sepcial Judge Module By JGShining)
 

Recommend
JGShining
*/


#include <bitset>
#include <iostream>
#include <cstring>

using namespace std;

int goalStatus; //目标状态
bitset<362880> Flags; //节点是否扩展的标记
const int MAXS = 400000;
char result[MAXS]; //结果
struct Node 
{
	int status; //状态，即排序的编号
	int father; //父结点指针
	char move; //父结点到本节点的移动方式
	Node(int s, int f, char m)
		:status(s), father(f), move(m) {}
	Node() { }
};

Node myQueue[MAXS]; //状态队列，状态总数362880 = 9！
int qHead, qTail; //队头指针和队尾指针
char sz4Moves[] = "udrl"; //四种动作
unsigned int factorial[21]; //存放0-20的阶乘

/*
perInt里存放着整数0到len-1的一个排列，
求它是第几个排列。
*/
unsigned int getPermutationNumForInt(int *perInt, int len)
{
	unsigned int num = 0;
	bool used[21];
	memset(used, 0, sizeof(bool)*len);
	for (int i = 0; i < len; ++i) {
		unsigned int n = 0;
		for (int j = 0; j < perInt[i]; ++j) {
			if (!used[j])
				++n;
		}
		num += n*factorial[len - i - 1];
		used[perInt[i]] = true;
	}
	return num;
}

/*
给定排列，求序号。[s1, s1+len)里面存放着第0号排列
[s2, s2+len)是要求序号的排列
排列的每个元素都不一样，返回排列的编号
*/
template<typename T>
unsigned int getPermutationNum(T s1, T s2, int len)
{
	int *perInt = new int[len];
	for (int i = 0; i < len; ++i) 
		for (int j = 0; j < len; ++j) {
			if (*(s2 + i) == *(s1 + j)) {
				perInt[i] = j;
				break;
			}
		}

	unsigned int num = getPermutationNumForInt(perInt, len);
	delete[] perInt;
	return num;
}

/*
根据排列编号，生成排列，len不能超过21
[s1, s1+len)里面存放着第0号排列permutation，
排列的每个元素都不一样，
要转换成[0,len-1]的整数排列
*/
template<typename T>
void genPermutationByNum(T s1, T s2, int len, unsigned int No)
{
	int *perInt = new int[len];
	int *used = new int[len];
	memset(used, 0, sizeof(bool)*len);
	for (int i = 0; i < len; ++i) {
		unsigned int tmp;
		int n = 0;
		int j;
		for (j = 0; j < len; ++j) {
			if (!used[j]) {
				if (factorial[len - i - 1] >= No + 1)
					break;
				else
					No -= factorial[len - i - 1];
			}
		}
		perInt[i] = j;
		used[j] = true;
	}

	for (int i = 0; i < len; ++i)
		*(s2 + i) = *(s1 + perInt[i]);

	delete[] perInt; delete[] used;
}

/*
字符串形式的状态，转化为整数形式的状态（排列序号）
*/
int StrStatusToIntStatus(const char *strStatus)
{
	return getPermutationNum("012345678", strStatus, 9);
}


/*
整数形式的状态（排列序号），转化为字符串形式的状态
*/
void IntStatusToStrStatus(int n, char *strStatus)
{
	genPermutationByNum((char*)"012345678", strStatus, 9, n);
}


/*
求从nStatus经过cMove移动后得到的新状态。
若移动不可行，则返回-1
*/
int newStatus(int nStatus, char cMove)
{
	char szTmp[20]; int nZeroPos;
	IntStatusToStrStatus(nStatus, szTmp);
	for (int i = 0; i < 9; ++i) 
		if (szTmp[i] == '0') {
			nZeroPos = i;
			break;
		}//返回空格位置

	switch (cMove) {
		case 'u':if (nZeroPos - 3 < 0)//空格在第一行
					return -1;
				 else {
					 szTmp[nZeroPos] = szTmp[nZeroPos - 3];
					 szTmp[nZeroPos - 3] = '0';
				 }
				 break;

		case 'd':if (nZeroPos + 3 > 8) //空格在第三行
					return -1;
				 else {
					 szTmp[nZeroPos] = szTmp[nZeroPos + 3];
					 szTmp[nZeroPos + 3] = '0';
				 }
				 break;

		case 'l':if (nZeroPos % 3 == 0) //空格在第一列
					return -1;
				 else {
					 szTmp[nZeroPos] = szTmp[nZeroPos - 1];
					 szTmp[nZeroPos - 1] = '0';
				 }
				 break;

		case 'r':if (nZeroPos % 3 == 2) //空格在第三列
					return -1;
				 else {
					 szTmp[nZeroPos] = szTmp[nZeroPos + 1];
					 szTmp[nZeroPos + 1] = '0';
				 }
				 break;
	}

	return StrStatusToIntStatus(szTmp);
}

/*
寻找从初始状态nStatus到目标的路径
*/
bool bfs(int nStatus)
{
	int nNewStatus;
	Flags.reset(); //清除所有扩展标记
	qHead = 0, qTail = 1;
	myQueue[qHead] = Node(nStatus, -1, 0);
	while (qHead != qTail) { //队列不为空
		nStatus = myQueue[qHead].status;
		if (nStatus == goalStatus)
			return true;
		for (int i = 0; i < 4; ++i) { //尝试4种移动
			nNewStatus = newStatus(nStatus, sz4Moves[i]);
			if (nNewStatus == -1)
				continue;
			if (Flags[nNewStatus]) //可扩展标记已经存在，则不入队列
				continue;

			Flags.set(nNewStatus, true);//设上已扩展的标记
			myQueue[qTail++] = Node(nNewStatus, qHead, sz4Moves[i]);
		}
		++qHead;
	}

	return false;
}

int main(int argc, char* argv[])
{
	freopen("input.txt", "r", stdin);
	factorial[0] = factorial[1] = 1;
	for (int i = 2; i < 21; ++i)
		factorial[i] = i * factorial[i - 1];
	goalStatus = StrStatusToIntStatus("123456780");
	char szLine[50]; char szLine2[21];
	while (cin.getline(szLine, 48)) {
		int i, j;
		//将输入的原始字符串变为数字字符串
		for (i = 0, j = 0; szLine[i]; ++i) {
			if (szLine[i] != ' ') {
				if (szLine[i] == 'x')
					szLine2[j++] = '0';
				else
					szLine2[j++] = szLine[i];
			}
		}
		szLine2[j] = 0; //字符串形式的初始状态
		int sumGoal = 0;//从此往后用奇偶性判断是否有解
		for (int i = 0; i < 8; ++i)
			sumGoal += i - 1;
		int sumOri = 0;
		for (int i = 0; i < 9; ++i) {
			if (szLine2[i] == '0')
				continue;
			for (int j = 0; j < i; ++j) {
				if (szLine2[j] < szLine2[i]
					&& szLine2[j] != '0')
					++sumOri;
			}
		}

		//用奇偶性判断是否有解
		if (sumOri % 2 != sumGoal % 2) {
			cout << "unsolvable\n";
			continue;
		}

		if (bfs(StrStatusToIntStatus(szLine2))) {
			int nMoves = 0;
			int nPos = qHead;
			do { //通过father找到成功的状态序列，输出相应步骤
				result[nMoves++] = myQueue[nPos].move;
				nPos = myQueue[nPos].father;
			} while (nPos);//nPos=0说明已经回退到初始状态了
			for (int i = nMoves - 1; i >= 0; --i)
				cout << result[i];
		}
		else
			cout << "unsolvable\n";
	}
}