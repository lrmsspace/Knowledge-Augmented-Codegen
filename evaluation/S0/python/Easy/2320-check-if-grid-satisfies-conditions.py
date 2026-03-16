# Source: https://leetcode.com/problems/check-if-grid-satisfies-conditions/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 2D matrix grid of size m x n. You need to check if each cell grid[i][j] is:
#
#
# 	Equal to the cell below it, i.e. grid[i][j] == grid[i + 1][j] (if it exists).
# 	Different from the cell to its right, i.e. grid[i][j] != grid[i][j + 1] (if it exists).
#
#
# Return true if all the cells satisfy these conditions, otherwise, return false.
#
# Example:
# Input: grid = [[1,0,2],[1,0,2]]
#
# Output: true
#
# Explanation:
#
#
#
# All the cells in the grid satisfy the conditions.
#
# Constraints:
# 1 <= n, m <= 10
# 	0 <= grid[i][j] <= 9
#

class Solution(object):
    def satisfiesConditions(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: bool
        """
        rows = len(grid)
        cols = len(grid[0])

        for i in range(rows):
            for j in range(cols):
                # Check the cell below
                if i + 1 < rows:
                    if grid[i][j] != grid[i + 1][j]:
                        return False
                # Check the cell to the right
                if j + 1 < cols:
                    if grid[i][j] == grid[i][j + 1]:
                        return False

        return True