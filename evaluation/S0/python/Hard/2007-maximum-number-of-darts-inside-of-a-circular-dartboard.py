# Source: https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/   |   Difficulty: Hard
#
# Problem Description:
# Alice is throwing n darts on a very large wall. You are given an array darts where darts[i] = [xi, yi] is the position of the ith dart that Alice threw on the wall.
#
# Bob knows the positions of the n darts on the wall. He wants to place a dartboard of radius r on the wall so that the maximum number of darts that Alice throws lie on the dartboard.
#
# Given the integer r, return the maximum number of darts that can lie on the dartboard.
#
# Example:
# Input: darts = [[-2,0],[2,0],[0,2],[0,-2]], r = 2
# Output: 4
# Explanation: Circle dartboard with center in (0,0) and radius = 2 contain all points.
#
# Constraints:
# 1 <= darts.length <= 100
# 	darts[i].length == 2
# 	-104 <= xi, yi <= 104
# 	All the darts are unique
# 	1 <= r <= 5000
#

class Solution(object):
    def numPoints(self, darts, r):
        """
        :type darts: List[List[int]]
        :type r: int
        :rtype: int
        """
        from math import sqrt, atan2, pi

        def get_circle_centers(p1, p2, r):
            mid_x = (p1[0] + p2[0]) / 2
            mid_y = (p1[1] + p2[1]) / 2
            d_sq = (p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2
            if d_sq > (2 * r) ** 2:
                return []
            h = sqrt(r ** 2 - (d_sq / 4))
            dx = (p2[0] - p1[0]) / sqrt(d_sq)
            dy = (p2[1] - p1[1]) / sqrt(d_sq)
            center1 = (mid_x + h * dy, mid_y - h * dx)
            center2 = (mid_x - h * dy, mid_y + h * dx)
            return [center1, center2]

        def count_points(center):
            count = 0
            for dart in darts:
                if (dart[0] - center[0]) ** 2 + (dart[1] - center[1]) ** 2 <= r ** 2 + 1e-9:
                    count += 1
            return count

        max_count = 1
        n = len(darts)
        for i in range(n):
            for j in range(i + 1, n):
                centers = get_circle_centers(darts[i], darts[j], r)
                for center in centers:
                    max_count = max(max_count, count_points(center))

        return max_count