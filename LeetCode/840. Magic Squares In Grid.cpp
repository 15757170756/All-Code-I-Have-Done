/*
840. Magic Squares In Grid
DescriptionHintsSubmissionsDiscussSolution
A 3 x 3 magic square is a 3 x 3 grid 
filled with distinct numbers from 1 to 9 
such that each row, column, and both diagonals all have the same sum.

Given an grid of integers, how many 3 x 3 "magic square" 
subgrids are there?  (Each subgrid is contiguous).

 

Example 1:

Input: [[4,3,8,4],
        [9,5,1,9],
        [2,7,6,2]]
Output: 1
Explanation: 
The following subgrid is a 3 x 3 magic square:
438
951
276

while this one is not:
384
519
762

In total, there is only one magic square inside the given grid.
Note:

1 <= grid.length <= 10
1 <= grid[0].length <= 10
0 <= grid[i][j] <= 15
Seen this question in a real interview before?  
Subscribe to see which companies asked this question.

Related Topics 
*/


class Solution {
public:
	bool isMagic(vector<int> &magicSquare)
	{
		if ((magicSquare[0] + magicSquare[8])
			!= (magicSquare[2] + magicSquare[6]))
			return false;
		int row1 = 0, row2 = 0, row3 = 0;
		for (int i = 0; i < magicSquare.size(); ++i) {
			if (i / 3 == 0)
				row1 += magicSquare[i];
			if (i / 3 == 1)
				row2 += magicSquare[i];
			if (i / 3 == 2)
				row3 += magicSquare[i];
		}

		int col1 = 0, col2 = 0, col3 = 0;
		for (int i = 0; i < magicSquare.size(); ++i) {
			if (i % 3 == 0)
				col1 += magicSquare[i];
			if (i % 3 == 1)
				col2 += magicSquare[i];
			if (i % 3 == 2)
				col3 += magicSquare[i];
		}

		sort(magicSquare.begin(), magicSquare.end());
		for (int i = 0; i < magicSquare.size(); ++i)
			if (magicSquare[i] != (i + 1))
				return false;

		if ((row1 == row2 && row2 == row3)
			&& (col1 == col2 && col2 == col3))
			return true;
		else
			return false;
	}
	int numMagicSquaresInside(vector<vector<int>>& grid) {
		int cnt = 0;
		int rows = grid.size();
		if (rows < 1)
			return cnt;
		vector<int> magicSquare(9);
		int cols = grid[0].size();
		for (int i = 0; i <= rows - 3; ++i) {
			for (int j = 0; j <= cols - 3; ++j) {
				int idx = 0;
				for (int k1 = i, k2 = 0; k1 < i + 3; ++k1, ++k2) {
					for (int m1 = j, m2 = 0; m1 < j + 3; ++m1, ++m2) {
						magicSquare[idx++] = grid[k1][m1];
					}
				}
				if (isMagic(magicSquare))
					++cnt;
			}

		}
		return cnt;
	}
};

//Submission Result: Accepted 