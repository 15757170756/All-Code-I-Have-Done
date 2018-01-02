// C++ program for Kruskal's algorithm to find Minimum
// Spanning Tree of a given connected, undirected and
// weighted graph
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

// Creating shortcut for an integer pair
typedef  pair<int, int> iPair;

// Structure to represent a graph
struct Graph
{
	int V, E;
	vector< pair<int, iPair> > edges;

	// Constructor
	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
	}

	// Utility function to add an edge
	void addEdge(int u, int v, int w)
	{
		edges.push_back({ w, { u, v } });
	}

	// Function to find MST using Kruskal's
	// MST algorithm
	int kruskalMST();
};

// To represent Disjoint Sets
struct DisjointSets
{
	int *parent, *rnk;
	int n;

	// Constructor.
	DisjointSets(int n)
	{
		// Allocate memory
		this->n = n;
		parent = new int[n + 1];
		rnk = new int[n + 1];

		// Initially, all vertices are in
		// different sets and have rank 0.
		for (int i = 0; i <= n; i++)
		{
			rnk[i] = 0;

			//every element is parent of itself
			parent[i] = i;
		}
	}

	// Find the parent of a node 'u'
	// Path Compression
	int find(int u)
	{
		/* Make the parent of the nodes in the path
		from u--> parent[u] point to parent[u] */
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}

	// Union by rank
	void merge(int x, int y)
	{
		x = find(x), y = find(y);

		/* Make tree with smaller height
		a subtree of the other tree  */
		if (rnk[x] > rnk[y])
			parent[y] = x;
		else // If rnk[x] <= rnk[y]
			parent[x] = y;

		if (rnk[x] == rnk[y])
			rnk[y]++;
	}
};

/* Functions returns weight of the MST*/

int Graph::kruskalMST()
{
	int mst_wt = 0; // Initialize result

	// Sort edges in increasing order on basis of cost
	sort(edges.begin(), edges.end());

	// Create disjoint sets
	DisjointSets ds(V);

	// Iterate through all sorted edges
	vector< pair<int, iPair> >::const_iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
	{
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.find(u);
		int set_v = ds.find(v);

		// Check if the selected edge is creating
		// a cycle or not (Cycle is created if u
		// and v belong to same set)
		if (set_u != set_v)
		{
			// Current edge will be in the MST
			// so print it
			cout << u << " - " << v << endl;

			// Update MST weight
			mst_wt += it->first;

			// Merge two sets
			ds.merge(set_u, set_v);
		}
	}

	return mst_wt;
}

// Driver program to test above functions
int main()
{
	/* Let us create above shown weighted
	and unidrected graph */
	int V = 9, E = 14;
	Graph g(V, E);

	//  making above shown graph
	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);

	cout << "Edges of MST are \n";
	int mst_wt = g.kruskalMST();

	cout << "\nWeight of MST is " << mst_wt;

	return 0;
}
/*
Run on IDE
Output :

Edges of MST are
6 - 7
2 - 8
5 - 6
0 - 1
2 - 5
2 - 3
0 - 7
3 - 4

Weight of MST is 37
Optimization:
The above code can be optimized to stop the main loop of 
Kruskal when number of selected edges become V - 1.
We know that MST has V - 1 edges and 
there is no point iterating after V - 1 edges are selected.
We have not added this optimization to keep code simple.
*/















/*
OpenCV stitching模块中找最大生成树
*/
void findMaxSpanningTree(int num_images, const std::vector<MatchesInfo> &pairwise_matches,
	Graph &span_tree, std::vector<int> &centers)
{
	Graph graph(num_images);
	std::vector<GraphEdge> edges;

	// Construct images graph and remember its edges
	for (int i = 0; i < num_images; ++i)
	{
		for (int j = 0; j < num_images; ++j)
		{
			if (pairwise_matches[i * num_images + j].H.empty())
				continue;
			float conf = static_cast<float>(pairwise_matches[i * num_images + j].num_inliers);
			graph.addEdge(i, j, conf);
			edges.push_back(GraphEdge(i, j, conf));
		}
	}

	DisjointSets comps(num_images);
	span_tree.create(num_images);
	std::vector<int> span_tree_powers(num_images, 0);

	// Find maximum spanning tree
	sort(edges.begin(), edges.end(), std::greater<GraphEdge>());
	for (size_t i = 0; i < edges.size(); ++i)
	{
		int comp1 = comps.findSetByElem(edges[i].from);
		int comp2 = comps.findSetByElem(edges[i].to);
		if (comp1 != comp2)
		{
			comps.mergeSets(comp1, comp2);
			span_tree.addEdge(edges[i].from, edges[i].to, edges[i].weight);
			span_tree.addEdge(edges[i].to, edges[i].from, edges[i].weight);
			span_tree_powers[edges[i].from]++;
			span_tree_powers[edges[i].to]++;
		}
	}

	// Find spanning tree leafs
	std::vector<int> span_tree_leafs;
	for (int i = 0; i < num_images; ++i)
		if (span_tree_powers[i] == 1)
			span_tree_leafs.push_back(i);

	// Find maximum distance from each spanning tree vertex
	std::vector<int> max_dists(num_images, 0);
	std::vector<int> cur_dists;
	for (size_t i = 0; i < span_tree_leafs.size(); ++i)
	{
		cur_dists.assign(num_images, 0);
		span_tree.walkBreadthFirst(span_tree_leafs[i], IncDistance(cur_dists));
		for (int j = 0; j < num_images; ++j)
			max_dists[j] = std::max(max_dists[j], cur_dists[j]);
	}

	// Find min-max distance
	int min_max_dist = max_dists[0];
	for (int i = 1; i < num_images; ++i)
		if (min_max_dist > max_dists[i])
			min_max_dist = max_dists[i];

	// Find spanning tree centers
	centers.clear();
	for (int i = 0; i < num_images; ++i)
		if (max_dists[i] == min_max_dist)
			centers.push_back(i);
	CV_Assert(centers.size() > 0 && centers.size() <= 2);
}

