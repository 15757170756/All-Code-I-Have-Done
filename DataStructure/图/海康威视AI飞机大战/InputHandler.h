#ifndef INCLUDE_INPUTHANDLER_H_
#define INCLUDE_INPUTHANDLER_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include "SquareGraph.h"
using namespace std;

class InputHandler {
public:
	SquareGraph readMap(vector<vector<char>> &matrix);
};

#endif /* INCLUDE_INPUTHANDLER_H_ */
