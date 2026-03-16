# Source: https://leetcode.com/problems/maximum-difference-score-in-a-grid/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n matrix grid consisting of positive integers. You can move from a cell in the matrix to any other cell that is either to the bottom or to the right (not necessarily adjacent). The score of a move from a cell with the value c1 to a cell with the value c2 is c2 - c1.
#
# You can start at any cell, and you have to make at least one move.
#
# Return the maximum total score you can achieve.
#
# Example:
# Input: grid = [[9,5,7,3],[8,9,6,1],[6,7,14,3],[2,5,3,1]]
#
# Output: 9
#
# Explanation: We start at the cell (0, 1), and we perform the following moves:
# - Move from the cell (0, 1) to (2, 1) with a score of 7 - 5 = 2.
# - Move from the cell (2, 1) to (2, 2) with a score of 14 - 7 = 7.
# The total score is 2 + 7 = 9.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	2 <= m, n <= 1000
# 	4 <= m * n <= 105
# 	1 <= grid[i][j] <= 105
#

class Solution(object):
    def maxScore(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        max_diff = [[float('-inf')] * n for _ in range(m)]
        
        for i in range(m):
            for j in range(n):
                if i == 0 and j == 0:
                    continue
                if i > 0:
                    max_diff[i][j] = max(max_diff[i][j], grid[i][j] - grid[i-1][j] + (max_diff[i-1][j] if max_diff[i-1][j] != float('-inf') else 0))
                if j > 0:
                    max_diff[i][j] = max(max_diff[i][j], grid[i][j] - grid[i][j-1] + (max_diff[i][j-1] if max_diff[i][j-1] != float('-inf') else 0))
        
        return max(max(row) for row in max_diff)