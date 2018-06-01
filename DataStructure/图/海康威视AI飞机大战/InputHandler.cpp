#include "InputHandler.h"

SquareGraph InputHandler::readMap(vector<vector<char>> &matrix) 
{
	int xLines = matrix.size();
	int yLines = matrix[0].size();
	char type;

	SquareGraph graph(xLines, yLines);
	for(int i = 0; i<xLines;i++){
		for(int j=0; j<yLines; j++) {
			if(matrix[i][j] == 'T') {
				graph.setFirstRobotPos(make_pair(i,j));
				type = ' ';
			}
			else if (matrix[i][j] == 'G'){
				graph.setSecondRobotPos(make_pair(i, j));
				type = ' ';
			}
			else
				type = matrix[i][j];
			graph.setCellValue(make_pair(i, j), type);
		}
	}
//	vector<Node> path = graph.executeAStar();
//	cout << "The total number of moves from distance to the target are : " << path.size() << endl;;
//	//cout << "You want to see the whole path to the target ? (y/n) " << endl;
//	string response = "y";
//	if(response.compare("y") == 0 ){
//		graph.printPath(path);
//	}
	return graph;
}
