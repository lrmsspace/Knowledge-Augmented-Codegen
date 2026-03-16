# Source: https://leetcode.com/problems/length-of-the-longest-increasing-path/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D array of integers coordinates of length n and an integer k, where 0 <= k < n.
#
# coordinates[i] = [xi, yi] indicates the point (xi, yi) in a 2D plane.
#
# An increasing path of length m is defined as a list of points (x1, y1), (x2, y2), (x3, y3), ..., (xm, ym) such that:
#
#
# 	xi < xi + 1 and yi < yi + 1 for all i where 1 <= i < m.
# 	(xi, yi) is in the given coordinates for all i where 1 <= i <= m.
#
#
# Return the maximum length of an increasing path that contains coordinates[k].
#
# Example:
# Input: coordinates = [[3,1],[2,2],[4,1],[0,0],[5,3]], k = 1
#
# Output: 3
#
# Explanation:
#
# (0, 0), (2, 2), (5, 3) is the longest increasing path that contains (2, 2).
#
# Constraints:
# 1 <= n == coordinates.length <= 105
# 	coordinates[i].length == 2
# 	0 <= coordinates[i][0], coordinates[i][1] <= 109
# 	All elements in coordinates are distinct.
# 	0 <= k <= n - 1
#

class Solution(object):
    def maxPathLength(self, coordinates, k):
        """
        :type coordinates: List[List[int]]
        :type k: int
        :rtype: int
        """
        n = len(coordinates)
        x_sorted = sorted(coordinates)
        y_sorted = sorted(coordinates, key=lambda x: x[1])
        
        dp_x = [1] * n
        dp_y = [1] * n
        
        coord_to_index = {tuple(coord): i for i, coord in enumerate(coordinates)}
        
        for i in range(n):
            for j in range(i):
                if x_sorted[j][0] < x_sorted[i][0] and x_sorted[j][1] < x_sorted[i][1]:
                    dp_x[i] = max(dp_x[i], dp_x[j] + 1)
                if y_sorted[j][0] < y_sorted[i][0] and y_sorted[j][1] < y_sorted[i][1]:
                    dp_y[i] = max(dp_y[i], dp_y[j] + 1)
        
        target_coord = tuple(coordinates[k])
        target_index_x = x_sorted.index(target_coord)
        target_index_y = y_sorted.index(target_coord)
        
        return max(dp_x[target_index_x], dp_y[target_index_y])