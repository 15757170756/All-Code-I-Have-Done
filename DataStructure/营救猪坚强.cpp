/*
Description
4月16日，日本熊本地区强震后，受灾严重的阿苏市一养猪场倒塌，幸运的是，
猪圈里很多头猪依然坚强存活。当地15名消防员耗时一天解救围困的“猪坚强”。
不过与在废墟中靠吃木炭饮雨水存活36天的中国汶川“猪坚强”相比，
熊本的猪可没那么幸运，因为它们最终还是没能逃过被送往屠宰场的命运。
我们假设“猪坚强”被困在一个N*M的废墟中，
其中“@”表示“猪坚强”的位置，“.”表示可以直接通过的空地，“#”表示不能拆毁的障碍物，“*”表示可以拆毁的障碍物，
那么请问消防员至少要拆毁多少个障碍物，才能从废墟中救出“猪坚强”送往屠宰场？
（当“猪坚强”通过空地或被拆毁的障碍物移动到废墟边缘时，视作被救出废墟）
Input
多组数据，第一行有一个整数T，表示有T组数据。（T<=100）
以下每组数据第一行有两个整数N和M。(1<=N,M<=100)
接着N行，每行有一个长度为M的字符串。
Output
一个整数，为最少拆毁的障碍物数量,如果不能逃离废墟，输出-1。

Sample Input
3
3 3
###
#@*
***
3 4
####
#@.*
**.*
3 3
.#.
#@#
.#.
Sample Output
1
0
-1
*/

#include<iostream>
#include<queue>
using namespace std;
struct Node{
	int x;
	int y;
	int z;
};

struct cmp{
	bool operator()(Node a, Node b){
		return a.z > b.z;
	}
};

char ch[100][101];

int main(){
	int t;
	cin >> t;
	while (t--){
		int n, m;
		cin >> n >> m;
		for (int i = 0; i < n; i++) cin >> ch[i];
		int a, b;
		a = -1;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				if (ch[i][j] == '@'){
					a = i;
					b = j;
					break;
				}
			}
			if (a != -1) break;
		}
		priority_queue<Node, vector<Node>, cmp> q;
		int ans = -1;
		struct Node *node = new struct Node;
		node->x = a;
		node->y = b;
		node->z = 0;
		q.push(*node);
		ch[node->x][node->y] = '#';
		bool flag = false;
		while (!q.empty()){
			struct Node *now = new struct Node;
			*now = q.top();
			q.pop();
			//            cout << "now " << now->x << "  " << now->y << "  " << now->z << endl;
			if (now->x == 0 || now->x == n - 1 || now->y == 0 || now->y == m - 1){
				ans = now->z;
				break;
			}
			else{
				if (now->y - 1 >= 0){
					if (ch[now->x][now->y - 1] == '.'){
						struct Node *temp = new struct Node;
						temp->x = now->x;
						temp->y = now->y - 1;
						temp->z = now->z;
						q.push(*temp);
						//                        cout << "push " << temp->x << "  " << temp->y << "  " << temp->z << endl;
						ch[now->x][now->y - 1] = '#';
					}
					else if (ch[now->x][now->y - 1] == '*'){
						struct Node *temp = new struct Node;
						temp->x = now->x;
						temp->y = now->y - 1;
						temp->z = now->z + 1;
						q.push(*temp);
						//                        cout << "push " << temp->x << "  " << temp->y << "  " << temp->z << endl;
						ch[now->x][now->y - 1] = '#';
					}
				}
				if (now->y + 1 <= m - 1){
					if (ch[now->x][now->y + 1] == '.'){
						struct Node *temp = new struct Node;
						temp->x = now->x;
						temp->y = now->y + 1;
						temp->z = now->z;
						q.push(*temp);
						//                        cout << "push " << temp->x << "  " << temp->y << "  " << temp->z << endl;
						ch[now->x][now->y + 1] = '#';
					}
					else if (ch[now->x][now->y + 1] == '*'){
						struct Node *temp = new struct Node;
						temp->x = now->x;
						temp->y = now->y + 1;
						temp->z = now->z + 1;
						q.push(*temp);
						//                        cout << "push " << temp->x << "  " << temp->y << "  " << temp->z << endl;
						ch[now->x][now->y + 1] = '#';
					}
				}
				if (now->x - 1 >= 0){
					if (ch[now->x - 1][now->y] == '.'){
						struct Node *temp = new struct Node;
						temp->x = now->x - 1;
						temp->y = now->y;
						temp->z = now->z;
						q.push(*temp);
						//                        cout << "push " << temp->x << "  " << temp->y << "  " << temp->z << endl;
						ch[now->x - 1][now->y] = '#';
					}
					else if (ch[now->x - 1][now->y] == '*'){
						struct Node *temp = new struct Node;
						temp->x = now->x - 1;
						temp->y = now->y;
						temp->z = now->z + 1;
						q.push(*temp);
						//                        cout << "push " << temp->x << "  " << temp->y << "  " << temp->z << endl;
						ch[now->x - 1][now->y] = '#';
					}
				}
				if (now->x + 1 <= n - 1){
					if (ch[now->x + 1][now->y] == '.'){
						struct Node *temp = new struct Node;
						temp->x = now->x + 1;
						temp->y = now->y;
						temp->z = now->z;
						q.push(*temp);
						//                        cout << "push " << temp->x << "  " << temp->y << "  " << temp->z << endl;
						ch[now->x + 1][now->y] = '#';
					}
					else if (ch[now->x + 1][now->y] == '*'){
						struct Node *temp = new struct Node;
						temp->x = now->x + 1;
						temp->y = now->y;
						temp->z = now->z + 1;
						q.push(*temp);
						//                        cout << "push " << temp->x << "  " << temp->y << "  " << temp->z << endl;
						ch[now->x + 1][now->y] = '#';
					}
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}