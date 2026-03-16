# Source: https://leetcode.com/problems/minimum-area-rectangle/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of points in the X-Y plane points where points[i] = [xi, yi].
#
# Return the minimum area of a rectangle formed from these points, with sides parallel to the X and Y axes. If there is not any such rectangle, return 0.
#
# Example:
# Input: points = [[1,1],[1,3],[3,1],[3,3],[2,2]]
# Output: 4
#
# Constraints:
# 1 <= points.length <= 500
# 	points[i].length == 2
# 	0 <= xi, yi <= 4 * 104
# 	All the given points are unique.
#

class Solution(object):
    def minAreaRect(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        point_set = set(map(tuple, points))
        min_area = float('inf')
        
        for i in range(len(points)):
            for j in range(i + 1, len(points)):
                p1, p2 = points[i], points[j]
                
                if p1[0] != p2[0] and p1[1] != p2[1]:
                    if (p1[0], p2[1]) in point_set and (p2[0], p1[1]) in point_set:
                        area = abs(p1[0] - p2[0]) * abs(p1[1] - p2[1])
                        min_area = min(min_area, area)
        
        return 0 if min_area == float('inf') else min_area