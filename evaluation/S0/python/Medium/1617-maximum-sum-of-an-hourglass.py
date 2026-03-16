# Source: https://leetcode.com/problems/maximum-sum-of-an-hourglass/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n integer matrix grid.
#
# We define an hourglass as a part of the matrix with the following form:
#
# Return the maximum sum of the elements of an hourglass.
#
# Note that an hourglass cannot be rotated and must be entirely contained within the matrix.
#
# Example:
# Input: grid = [[6,2,1,3],[4,2,1,5],[9,2,8,7],[4,1,2,9]]
# Output: 30
# Explanation: The cells shown above represent the hourglass with the maximum sum: 6 + 2 + 1 + 2 + 9 + 2 + 8 = 30.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	3 <= m, n <= 150
# 	0 <= grid[i][j] <= 106
#

class Solution(object):
    def maxSum(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        max_sum = 0
        rows = len(grid)
        cols = len(grid[0])
        
        for i in range(rows - 2):
            for j in range(cols - 2):
                hourglass_sum = (grid