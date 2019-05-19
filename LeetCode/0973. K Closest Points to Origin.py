class Solution(object):
    def kClosest(self, points, K):
        points.sort(key = lambda P: P[0]**2 + P[1]**2)
        return points[:K]


# Success
# Details 
# Runtime: 568 ms, faster than 100.00% of Python3 
# online submissions for K Closest Points to Origin.  