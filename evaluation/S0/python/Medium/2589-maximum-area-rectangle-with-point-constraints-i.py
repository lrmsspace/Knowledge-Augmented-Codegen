# Source: https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array points where points[i] = [xi, yi] represents the coordinates of a point on an infinite plane.
#
# Your task is to find the maximum area of a rectangle that:
#
#
# 	Can be formed using four of these points as its corners.
# 	Does not contain any other point inside or on its border.
# 	Has its edges parallel to the axes.
#
#
# Return the maximum area that you can obtain or -1 if no such rectangle is possible.
#
# Example:
# Input: points = [[1,1],[1,3],[3,1],[3,3]]
#
# Output: 4
#
# Explanation:
#
#
#
# We can make a rectangle with these 4 points as corners and there is no other point that lies inside or on the border. Hence, the maximum possible area would be 4.
#
# Constraints:
# 1 <= points.length <= 10
# 	points[i].length == 2
# 	0 <= xi, yi <= 100
# 	All the given points are unique.
#

class Solution(object):
    def maxRectangleArea(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        point_set = set(map(tuple, points))
        max_area = -1

        n = len(points)
        for i in range(n):
            for j in range(i + 1, n):
                for k in range(j + 1, n):
                    for l in range(k + 1, n):
                        p1, p2, p3, p4 = points[i], points[j], points[k], points[l]
                        if self.is_rectangle(p1, p2, p3, p4):
                            area = self.calculate_area(p1, p2, p3, p4)
                            if self.is_valid_rectangle(p1, p2, p3, p4, point_set):
                                max_area = max(max_area, area)

        return max_area