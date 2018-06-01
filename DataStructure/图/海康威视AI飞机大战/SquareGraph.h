#ifndef SQUAREGRAPH_H_
#define SQUAREGRAPH_H_

#include <vector>
#include <algorithm>
#include <set>
#include <list>
#include <queue>
#include <math.h>
#include <iostream>
#include "Node.h"
using namespace std;

class SquareGraph 
{
private:
	vector<vector<Node>> map;
	pair<int, int> firstRobotPos;
	pair<int, int> secondRobotPos;

public:
	SquareGraph(int xLines, int yLines);
	Node* getCellValue(pair<int, int> coord);
	void setCellValue(pair<int, int> coord, char value);
	void setFirstRobotPos(pair<int, int> coord);
	void setSecondRobotPos(pair<int, int> coord);
	pair<int, int> getFirstRobotPos();
	pair<int, int> getSecondRobotPos();
	float calculateDistance(pair<int, int> from, pair<int, int> to);
	void calculateAllCosts();
	bool isInsideMap(pair<int, int> coord);
	class compareNodes{
		public:
		bool operator()(Node n1, Node n2);
	};
	set<Node> getNeighbours(Node n);
	vector<Node> executeAStar();
	vector<Node> reconstructPath(Node* to, Node* from);
	void printPath(vector<Node> path);
	priority_queue<Node , vector<Node>, compareNodes> openNodes;
	priority_queue<Node, vector<Node>, compareNodes> closedNodes;
};

#endif /* SQUAREGRAPH_H_ */
