/*
973. K Closest Points to Origin
Easy

35

10

Favorite

Share
We have a list of points on the plane.  Find the K closest points to the origin (0, 0).

(Here, the distance between two points on a plane is the Euclidean distance.)

You may return the answer in any order.  The answer is guaranteed to be unique (except for the order that it is in.)

 

Example 1:

Input: points = [[1,3],[-2,2]], K = 1
Output: [[-2,2]]
Explanation: 
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest K = 1 points from the origin, so the answer is just [[-2,2]].
Example 2:

Input: points = [[3,3],[5,-1],[-2,4]], K = 2
Output: [[3,3],[-2,4]]
(The answer [[-2,4],[3,3]] would also be accepted.)
 

Note:

1 <= K <= points.length <= 10000
-10000 < points[i][0] < 10000
-10000 < points[i][1] < 10000
Accepted
5,356
Submissions
7,768
*/

class Solution {
public:
	vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
		vector<pair<float, int>> vp(points.size());
		for (int i = 0; i < points.size(); ++i) {
			int x = points[i][0];
			int y = points[i][1];
			float dis = x*x + y*y;
			vp[i].first = dis, vp[i].second = i;
		}
		sort(vp.begin(), vp.end());
		vector<vector<int>> res(K);
		for (int i = 0; i < K; ++i) {
			int x = points[vp[i].second][0];
			int y = points[vp[i].second][1];
			vector<int> temp{ x,y };
			res[i] = temp;
		}
		return res;
	}
};
/*
Success
Details 
Runtime: 280 ms, faster than 0.00% of C++ online submissions for K 
Closest Points to Origin.
*/



