# Source: https://leetcode.com/problems/number-of-boomerangs/   |   Difficulty: Medium
#
# Problem Description:
# You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
#
# Return the number of boomerangs.
#
# Example:
# Input: points = [[0,0],[1,0],[2,0]]
# Output: 2
# Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].
#
# Constraints:
# n == points.length
# 	1 <= n <= 500
# 	points[i].length == 2
# 	-104 <= xi, yi <= 104
# 	All the points are unique.
#

class Solution(object):
    def numberOfBoomerangs(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        total_boomerangs = 0
        
        for i in range(len(points)):
            distance_count = {}
            for j in range(len(points)):
                if i != j:
                    dx = points[i][0] - points[j][0]
                    dy = points[i][1] - points[j][1]
                    dist_sq = dx * dx + dy * dy
                    
                    if dist_sq in distance_count:
                        distance_count[dist_sq] += 1
                    else:
                        distance_count[dist_sq] = 1
            
            for count in distance_count.values():
                if count > 1:
                    total_boomerangs += count * (count - 1)
        
        return total_boomerangs