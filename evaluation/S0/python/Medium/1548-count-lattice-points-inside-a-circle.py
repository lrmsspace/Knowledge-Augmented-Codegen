# Source: https://leetcode.com/problems/count-lattice-points-inside-a-circle/   |   Difficulty: Medium
#
# Problem Description:
# Given a 2D integer array circles where circles[i] = [xi, yi, ri] represents the center (xi, yi) and radius ri of the ith circle drawn on a grid, return the number of lattice points that are present inside at least one circle.
#
# Note:
#
#
# 	A lattice point is a point with integer coordinates.
# 	Points that lie on the circumference of a circle are also considered to be inside it.
#
# Example:
# Input: circles = [[2,2,1]]
# Output: 5
# Explanation:
# The figure above shows the given circle.
# The lattice points present inside the circle are (1, 2), (2, 1), (2, 2), (2, 3), and (3, 2) and are shown in green.
# Other points such as (1, 1) and (1, 3), which are shown in red, are not considered inside the circle.
# Hence, the number of lattice points present inside at least one circle is 5.
#
# Constraints:
# 1 <= circles.length <= 200
# 	circles[i].length == 3
# 	1 <= xi, yi <= 100
# 	1 <= ri <= min(xi, yi)
#

class Solution(object):
    def countLatticePoints(self, circles):
        """
        :type circles: List[List[int]]
        :rtype: int
        """
        points = set()
        
        for x_center, y_center, r in circles:
            for x in range(x_center - r, x_center + r + 1):
                for y in range(y_center - r, y_center + r + 1):
                    if (x - x_center) ** 2 + (y - y_center) ** 2 <= r ** 2:
                        points.add((x, y))
        
        return len(points)