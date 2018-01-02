//OpenCV上的图代码
#include <iostream>
#include <queue>
#include <vector>
#include <list>

using namespace::std;

//带权有向边
struct GraphEdge
{
	GraphEdge(int from, int to, float weight);
	bool operator <(const GraphEdge& other) const { return weight < other.weight; }
	bool operator >(const GraphEdge& other) const { return weight > other.weight; }

	int from, to;
	float weight;
};

inline GraphEdge::GraphEdge(int _from, int _to, float _weight)
	:from(_from), to(_to), weight(_weight) {}


class Graph
{
public:
	Graph(int num_vertices = 0) { create(num_vertices); }
	void create(int num_vertices) { edges_.assign(num_vertices, std::list<GraphEdge>()); }
	int numVertices() const { return static_cast<int>(edges_.size()); }
	void addEdge(int from, int to, float weight);
	template <typename B> B forEach(B body) const;
	template <typename B> B walkBreadthFirst(int from, B body) const;

private:
	std::vector< std::list<GraphEdge> > edges_;
};

void Graph::addEdge(int from, int to, float weight)
{
	edges_[from].push_back(GraphEdge(from, to, weight));
}

template <typename B>
B Graph::forEach(B body) const
{
	for (int i = 0; i < numVertices(); ++i)
	{
		std::list<GraphEdge>::const_iterator edge = edges_[i].begin();
		for (; edge != edges_[i].end(); ++edge)
			body(*edge);
	}
	return body;
}

template <typename B>
B Graph::walkBreadthFirst(int from, B body) const
{
	std::vector<bool> was(numVertices(), false);
	std::queue<int> vertices;

	was[from] = true;
	vertices.push(from);

	while (!vertices.empty())
	{
		int vertex = vertices.front();
		vertices.pop();

		std::list<GraphEdge>::const_iterator edge = edges_[vertex].begin();
		for (; edge != edges_[vertex].end(); ++edge)
		{
			if (!was[edge->to])
			{
				body(*edge);
				was[edge->to] = true;
				vertices.push(edge->to);
			}
		}
	}

	return body;
}