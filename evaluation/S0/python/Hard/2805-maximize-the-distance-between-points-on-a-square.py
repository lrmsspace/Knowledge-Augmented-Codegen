# Source: https://leetcode.com/problems/maximize-the-distance-between-points-on-a-square/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer side, representing the edge length of a square with corners at (0, 0), (0, side), (side, 0), and (side, side) on a Cartesian plane.
#
# You are also given a positive integer k and a 2D integer array points, where points[i] = [xi, yi] represents the coordinate of a point lying on the boundary of the square.
#
# You need to select k elements among points such that the minimum Manhattan distance between any two points is maximized.
#
# Return the maximum possible minimum Manhattan distance between the selected k points.
#
# The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.
#
# Example:
# Input: side = 2, points = [[0,2],[2,0],[2,2],[0,0]], k = 4
#
# Output: 2
#
# Explanation:
#
#
#
# Select all four points.
#
# Constraints:
# 1 <= side <= 109
# 	4 <= points.length <= min(4 * side, 15 * 103)
# 	points[i] == [xi, yi]
# 	The input is generated such that:
# 	
# 		points[i] lies on the boundary of the square.
# 		All points[i] are unique.
# 	
# 	
# 	4 <= k <= min(25, points.length)
#

class Solution(object):
    def maxDistance(self, side, points, k):
        """
        :type side: int
        :type points: List[List[int]]
        :type k: int
        :rtype: int
        """
        def manhattan(p1, p2):
            return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])

        def can_place(distance):
            selected = []
            for point in points:
                if all(manhattan(point, sel) >= distance for sel in selected):
                    selected.append(point)
                    if len(selected) == k:
                        return True
            return False

        left, right = 0, 2 * side
        answer = 0

        while left <= right:
            mid = (left + right) // 2
            if can_place(mid):
                answer = mid
                left = mid + 1
            else:
                right = mid - 1

        return answer