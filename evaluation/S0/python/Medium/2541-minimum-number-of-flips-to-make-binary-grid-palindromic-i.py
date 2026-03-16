# Source: https://leetcode.com/problems/minimum-number-of-flips-to-make-binary-grid-palindromic-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n binary matrix grid.
#
# A row or column is considered palindromic if its values read the same forward and backward.
#
# You can flip any number of cells in grid from 0 to 1, or from 1 to 0.
#
# Return the minimum number of cells that need to be flipped to make either all rows palindromic or all columns palindromic.
#
# Example:
# Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
#
# Output: 2
#
# Explanation:
#
#
#
# Flipping the highlighted cells makes all the rows palindromic.
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
        total_flips = 0

        for i in range((m + 1) // 2):
            for j in range((n + 1) // 2):
                cells = [
                    grid[i][j],
                    grid[m - 1 - i][j],
                    grid[i][n - 1 - j],
                    grid[m - 1 - i][n - 1 - j]
                ]
                count_ones = sum(cells)
                count_zeros = len(cells) - count_ones
                total_flips += min(count_ones, count_zeros)

        return total_flips