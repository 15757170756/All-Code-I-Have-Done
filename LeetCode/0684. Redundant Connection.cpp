/*
https://leetcode.com/problems/redundant-connection/

In this problem, a tree is an undirected graph that is connected and has no cycles.

The given input is a graph that started as a tree with N nodes (with distinct values 1, 2, ..., N), with one additional edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] with u < v, that represents an undirected edge connecting nodes u and v.

Return an edge that can be removed so that the resulting graph is a tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array. The answer edge [u, v] should be in the same format, with u < v.

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given undirected graph will be like this:
  1
 / \
2 - 3
Example 2:
Input: [[1,2], [2,3], [3,4], [1,4], [1,5]]
Output: [1,4]
Explanation: The given undirected graph will be like this:
5 - 1 - 2
    |   |
    4 - 3
Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.

Update (2017-09-26):
We have overhauled the problem description + test cases and specified clearly the graph is an undirected graph. For the directed graph follow up please see Redundant Connection II). We apologize for any inconvenience caused.

Seen this question in a real interview before?
*/



/*
Approach #1: DFS [Accepted]
Intuition and Algorithm

For each edge (u, v), traverse the graph with a depth-first search to see if we can connect u to v. If we can, then it must be the duplicate edge.


Complexity Analysis

Time Complexity: O(N^2)O(N 
2
 ) where NN is the number of vertices (and also the number of edges) in the graph. In the worst case, for every edge we include, we have to search every previously-occurring edge of the graph.

Space Complexity: O(N)O(N). The current construction of the graph has at most NN nodes.

Approach #2: Union-Find [Accepted]
Intuition and Algorithm

If we are familiar with a Disjoint Set Union (DSU) data structure, we can use this in a straightforward manner to solve the problem: we simply find the first edge occurring in the graph that is already connected. The rest of this explanation will focus on the details of implementing DSU.

A DSU data structure can be used to maintain knowledge of the connected components of a graph, and query for them quickly. In particular, we would like to support two operations:

dsu.find(node x), which outputs a unique id so that two nodes have the same id if and only if they are in the same connected component, and:

dsu.union(node x, node y), which draws an edge (x, y) in the graph, connecting the components with id find(x) and find(y) together.

To achieve this, we keep track of parent, which remembers the id of a smaller node in the same connected component. If the node is it's own parent, we call this the leader of that connected component.

A naive implementation of a DSU structure would look something like this:

Psuedocode


We use two techniques to improve the run-time complexity: path compression, and union-by-rank.

Path compression involves changing the x = parent[x] in the find function to parent[x] = find(parent[x]). Basically, as we compute the correct leader for x, we should remember our calculation.

Union-by-rank involves distributing the workload of find across leaders evenly. Whenever we dsu.union(x, y), we have two leaders xr, yr and we have to choose whether we want parent[x] = yr or parent[y] = xr. We choose the leader that has a higher following to pick up a new follower.
Specifically, the meaning of rank is that there are less than 2 ^ rank[x] followers of x. This strategy can be shown to give us better bounds for how long the recursive loop in dsu.find could run for.


Alternate Implementation of DSU without Union-By-Rank

 
Complexity Analysis

Time Complexity: O(N\alpha(N)) \approx O(N)O(Nα(N))≈O(N), where NN is the number of vertices (and also the number of edges) in the graph, and \alphaα is the Inverse-Ackermann function. We make up to NN queries of dsu.union, which takes (amortized) O(\alpha(N))O(α(N)) time. Outside the scope of this article, it can be shown why dsu.union has O(\alpha(N))O(α(N)) complexity, what the Inverse-Ackermann function is, and why O(\alpha(N))O(α(N)) is approximately O(1)O(1).

Space Complexity: O(N)O(N). The current construction of the graph (embedded in our dsu structure) has at most NN nodes.
*/




class Solution {
public:
	set<int> seen;
	const int max_edge_val = 1000;
	bool dfs(vector<vector<int>>& graph, int source, int target)
	{
		if (!seen.count(source)) {
			seen.emplace(source);
			if (source == target)
				return true;
			for (int nei : graph[source]) {
				if (dfs(graph, nei, target))
					return true;
			}
		}
		return false;
	}
	vector<int> findRedundantConnection(vector<vector<int>>& edges) {
		vector<vector<int>> graph(max_edge_val + 1);
		for (vector<int> edge : edges) {
			seen.clear();
			if (!graph[edge[0]].empty() &&
				!graph[edge[1]].empty() &&
				dfs(graph, edge[0], edge[1])) {
				return edge;
			}
			graph[edge[0]].emplace_back(edge[1]);
			graph[edge[1]].emplace_back(edge[0]);
		}
	}
};
//Runtime: 12 ms, faster than 18.91% of C++ 
//online submissions for Redundant Connection.



class DSU(object):
    def __init__(self):
        self.par = list(range(1001))
        self.rnk = [0] * 1001

    def find(self, x):
        if self.par[x] != x:
            self.par[x] = self.find(self.par[x])

        """
        or
        r = x
        while r != self.par[r]:
            r = self.par[r]
        
        i = x
        while self.par[i] != r:
            j = self.par[i]
            self.par[i] = r
            i = j
        return r
        """

        return self.par[x]

    def union(self, x, y):
        xr, yr = self.find(x), self.find(y)
        if xr == yr:
            return False
        elif self.rnk[xr] < self.rnk[yr]:
            self.par[xr] = yr
        elif self.rnk[xr] > self.rnk[yr]:
            self.par[yr] = xr
        else:
            self.par[yr] = xr
            self.rnk[xr] += 1
        return True

class Solution(object):
    def findRedundantConnection(self, edges):
        dsu = DSU()
        for edge in edges:
            if not dsu.union(*edge):
                return edge

//Runtime: 56 ms, faster than 39.44% of Python3 
//online submissions for Redundant Connection.