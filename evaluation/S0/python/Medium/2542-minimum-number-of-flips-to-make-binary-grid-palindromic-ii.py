# Source: https://leetcode.com/problems/minimum-number-of-flips-to-make-binary-grid-palindromic-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n binary matrix grid.
#
# A row or column is considered palindromic if its values read the same forward and backward.
#
# You can flip any number of cells in grid from 0 to 1, or from 1 to 0.
#
# Return the minimum number of cells that need to be flipped to make all rows and columns palindromic, and the total number of 1's in grid divisible by 4.
#
# Example:
# Input: grid = [[1,0,0],[0,1,0],[0,0,1]]
#
# Output: 3
#
# Explanation:
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m * n <= 2 * 105
# 	0 <= grid[i][j] <= 1
#

class Solution(object):
    def minFlips(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        total_ones = sum(sum(row) for row in grid)
        if total_ones % 4 != 0:
            return -1

        flips = 0
        for i in range((m + 1) // 2):
            for j in range((n + 1) // 2):
                cells = [
                    grid[i][j],
                    grid[i][n - j - 1] if j != n - j - 1 else None,
                    grid[m - i - 1][j] if i != m - i - 1 else None,
                    grid[m - i - 1][n - j - 1] if i != m - i - 1 and j != n - j - 1 else None
                ]
                cells = [cell for cell in cells if cell is not None]
                ones_count = sum(cells)
                zeros_count = len(cells) - ones_count
                flips += min(ones_count, zeros_count)

        return flips