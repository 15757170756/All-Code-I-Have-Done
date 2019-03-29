/*
https://leetcode.com/problems/redundant-connection-ii/description/


In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.

The given input is a directed graph that started as a rooted tree with N nodes (with distinct values 1, 2, ..., N), with one additional directed edge added. The added edge has two different vertices chosen from 1 to N, and was not an edge that already existed.

The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [u, v] that represents a directed edge connecting nodes u and v, where u is a parent of child v.

Return an edge that can be removed so that the resulting graph is a rooted tree of N nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array.

Example 1:
Input: [[1,2], [1,3], [2,3]]
Output: [2,3]
Explanation: The given directed graph will be like this:
  1
 / \
v   v
2-->3
Example 2:
Input: [[1,2], [2,3], [3,4], [4,1], [1,5]]
Output: [4,1]
Explanation: The given directed graph will be like this:
5 <- 1 -> 2
     ^    |
     |    v
     4 <- 3
Note:
The size of the input 2D-array will be between 3 and 1000.
Every integer represented in the 2D-array will be between 1 and N, where N is the size of the input array.
Seen this question in a real interview before?
*/




/*
This problem is very similar to "Redundant Connection". But the description on the parent/child relationships is much better clarified.

There are two cases for the tree structure to be invalid.
1) A node having two parents;
   including corner case: e.g. [[4,2],[1,5],[5,2],[5,3],[2,4]]
2) A circle exists
If we can remove exactly 1 edge to achieve the tree structure, a single node can have at most two parents. So my solution works in two steps.

1) Check whether there is a node having two parents. 
    If so, store them as candidates A and B, and set the second edge invalid. 
2) Perform normal union find. 
    If the tree is now valid 
           simply return candidate B
    else if candidates not existing 
           we find a circle, return current edge; 
    else 
           remove candidate A instead of B.
If you like this solution, please help upvote so more people can see.
*/

class Solution {
public:
    vector<int> findRedundantDirectedConnection(
    	vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> parent(n+1, 0), candA, candB;
        // step 1, check whether there is a node with two parents
        for (auto &edge:edges) {
            if (parent[edge[1]] == 0)
                parent[edge[1]] = edge[0]; 
            else {
                candA = {parent[edge[1]], edge[1]};
                candB = edge;
                edge[1] = 0;
            }
        } 
        // step 2, union find
        for (int i = 1; i <= n; i++) 
        	parent[i] = i;

        for (auto &edge:edges) {
            if (edge[1] == 0) 
            	continue;
            int u = edge[0], v = edge[1], pu = root(parent, u);
            // Now every node only has 1 parent, so root of v is implicitly v
            if (pu == v) {
                if (candA.empty()) 
                	return edge;
                return candA;
            }
            parent[v] = pu;
        }
        return candB;
    }
private:
    int root(vector<int>& parent, int k) {
        if (parent[k] != k) 
            parent[k] = root(parent, parent[k]);
        return parent[k];
    }
};














/*
Approach #1: Depth-First Search [Accepted]
Intuition

Starting from a rooted tree with N-1 edges and N vertices, let's enumerate the possibilities for the added "redundant" edge. If there is no loop, then either one vertex must have two parents (or no edge is redundant.) If there is a loop, then either one vertex has two parents, or every vertex has one parent.

In the first two cases, there are only two candidates for deleting an edge, and we can try removing the last one and seeing if that works. In the last case, the last edge of the cycle can be removed: for example, when 1->2->3->4->1->5, we want the last edge (by order of occurrence) in the cycle 1->2->3->4->1 (but not necessarily 1->5).

Algorithm

We'll first construct the underlying graph, keeping track of edges coming from nodes with multiple parents. After, we either have 2 or 0 candidates.

If there are no candidates, then every vertex has one parent, such as in the case 1->2->3->4->1->5. From any node, we walk towards it's parent until we revisit a node - then we must be inside the cycle, and any future seen nodes are part of that cycle. Now we take the last edge that occurs in the cycle.

Otherwise, we'll see if the graph induced by parent is a rooted tree. We again take the root by walking from any node towards the parent until we can't, then we perform a depth-first search on this root. If we visit every node, then removing the last of the two edge candidates is acceptable, and we should. Otherwise, we should remove the first of the two edge candidates.

In our solution, we use orbit to find the result upon walking from a node x towards it's parent repeatedly until you revisit a node or can't walk anymore. orbit(x).node (or orbit(x)[0] in Python) will be the resulting node, while orbit(x).seen (or orbit(x)[1]) will be all the nodes visited.


Complexity Analysis

Time Complexity: O(N)O(N) where NN is the number of vertices (and also the number of edges) in the graph. We perform a depth-first search.

Space Complexity: O(N)O(N), the size of the graph.
*/
class Solution(object):
    def findRedundantDirectedConnection(self, edges):
        N = len(edges)
        parent = {}
        candidates = []
        for u, v in edges:
            if v in parent:
                candidates.append((parent[v], v))
                candidates.append((u, v))
            else:
                parent[v] = u

        def orbit(node):
            seen = set()
            while node in parent and node not in seen:
                seen.add(node)
                node = parent[node]
            return node, seen

        root = orbit(1)[0]

        if not candidates:
            cycle = orbit(root)[1]
            for u, v in edges:
                if u in cycle and v in cycle:
                    ans = u, v
            return ans

        children = collections.defaultdict(list)
        for v in parent:
            children[parent[v]].append(v)

        seen = [True] + [False] * N
        stack = [root]
        while stack:
            node = stack.pop()
            if not seen[node]:
                seen[node] = True
                stack.extend(children[node])

        return candidates[all(seen)]