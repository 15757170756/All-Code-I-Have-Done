/*
847. Shortest Path Visiting All Nodes
User Accepted: 116
User Tried: 272
Total Accepted: 127
Total Submissions: 676
Difficulty: Hard


An undirected, connected graph of N nodes
 (labeled 0, 1, 2, ..., N-1) is given as graph.
graph.length = N, and j != i is in the list graph[i] exactly once, 
if and only if nodes i and j are connected.

Return the length of the shortest path that visits every node. 
You may start and stop at any node, 
you may revisit nodes multiple times, and you may reuse edges.


Example 1:

Input: [[1,2,3],[0],[0],[0]]
Output: 4
Explanation: One possible path is [1,0,2,0,3]
Example 2:

Input: [[1],[0,2,4],[1,3,4],[2],[1,2]]
Output: 4
Explanation: One possible path is [0,1,4,2,3]
 

Note:

1 <= graph.length <= 12
0 <= graph[i].length < graph.length
*/



/*
State has two keys: cover and head;
cover means the positions it's already pass;
head means the position it is now at.
*/

int shortestPathLength(vector<vector<int>>& graph) {
	queue<pair<int, int>> states;
	int length = graph.size();
	for (int i = 0; i < length; i++)
		states.push({(2 << i >> 1), i});
	vector<vector<int>> res((2 << length >> 1), vector<int>(length, 0));
	while (!states.empty()) {
		int nowCover = states.front().first;
		int nowHead = states.front().second;
		states.pop();
		if (nowCover == ((2 << length >> 1) - 1))
			return res[nowCover][nowHead];
		for (int j = 0; j < graph[nowHead].size(); j++) {
			int nextCover = nowCover, nextHead = graph[nowHead][j];
			if (!((nowCover >> graph[nowHead][j]) % 2) == 1)
				nextCover += ((2 << graph[nowHead][j]) >> 1); 
			if (res[nextCover][nextHead] == 0) {
				res[nextCover][nextHead] = res[nowCover][nowHead] + 1;
				states.push({nextCover, nextHead});
			}
		}
	}
	return -1;
}