# Source: https://leetcode.com/problems/minimum-area-rectangle-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of points in the X-Y plane points where points[i] = [xi, yi].
#
# Return the minimum area of any rectangle formed from these points, with sides not necessarily parallel to the X and Y axes. If there is not any such rectangle, return 0.
#
# Answers within 10-5 of the actual answer will be accepted.
#
# Example:
# Input: points = [[1,2],[2,1],[1,0],[0,1]]
# Output: 2.00000
# Explanation: The minimum area rectangle occurs at [1,2],[2,1],[1,0],[0,1], with an area of 2.
#
# Constraints:
# 1 <= points.length <= 50
# 	points[i].length == 2
# 	0 <= xi, yi <= 4 * 104
# 	All the given points are unique.
#

class Solution(object):
    def minAreaFreeRect(self, points):
        """
        :type points: List[List[int]]
        :rtype: float
        """
        point_set = set(map(tuple, points))
        min_area = float('inf')
        
        for i in range(len(points)):
            for j in range(len(points)):
                if i == j:
                    continue
                for k in range(len(points)):
                    if k == i or k == j:
                        continue
                    
                    p1 = points[i]
                    p2 = points[j]
                    p3 = points[k]
                    
                    # Calculate the coordinates of the fourth point
                    p4 = (p1[0] + p3[0] - p2[0], p1[1] + p3[1] - p2[1])
                    
                    if p4 in point_set:
                        # Calculate the area of the rectangle
                        area = self.distance(p1, p2) * self.distance(p1, p3)
                        min_area = min(min_area, area)
        
        return 0 if min_area == float('inf') else min_area