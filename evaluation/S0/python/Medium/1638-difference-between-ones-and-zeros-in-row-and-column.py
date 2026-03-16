# Source: https://leetcode.com/problems/difference-between-ones-and-zeros-in-row-and-column/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed m x n binary matrix grid.
#
# A 0-indexed m x n difference matrix diff is created with the following procedure:
#
#
# 	Let the number of ones in the ith row be onesRowi.
# 	Let the number of ones in the jth column be onesColj.
# 	Let the number of zeros in the ith row be zerosRowi.
# 	Let the number of zeros in the jth column be zerosColj.
# 	diff[i][j] = onesRowi + onesColj - zerosRowi - zerosColj
#
#
# Return the difference matrix diff.
#
# Example:
# Input: grid = [[0,1,1],[1,0,1],[0,0,1]]
# Output: [[0,0,4],[0,0,4],[-2,-2,2]]
# Explanation:
# - diff[0][0] = onesRow0 + onesCol0 - zerosRow0 - zerosCol0 = 2 + 1 - 1 - 2 = 0 
# - diff[0][1] = onesRow0 + onesCol1 - zerosRow0 - zerosCol1 = 2 + 1 - 1 - 2 = 0 
# - diff[0][2] = onesRow0 + onesCol2 - zerosRow0 - zerosCol2 = 2 + 3 - 1 - 0 = 4 
# - diff[1][0] = onesRow1 + onesCol0 - zerosRow1 - zerosCol0 = 2 + 1 - 1 - 2 = 0 
# - diff[1][1] = onesRow1 + onesCol1 - zerosRow1 - zerosCol1 = 2 + 1 - 1 - 2 = 0 
# - diff[1][2] = onesRow1 + onesCol2 - zerosRow1 - zerosCol2 = 2 + 3 - 1 - 0 = 4 
# - diff[2][0] = onesRow2 + onesCol0 - zerosRow2 - zerosCol0 = 1 + 1 - 2 - 2 = -2
# - diff[2][1] = onesRow2 + onesCol1 - zerosRow2 - zerosCol1 = 1 + 1 - 2 - 2 = -2
# - diff[2][2] = onesRow2 + onesCol2 - zerosRow2 - zerosCol2 = 1 + 3 - 2 - 0 = 2
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 105
# 	1 <= m * n <= 105
# 	grid[i][j] is either 0 or 1.
#

class Solution(object):
    def onesMinusZeros(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: List[List[int]]
        """
        m = len(grid)
        n = len(grid[0]) if m > 0 else 0

        ones_row = [0] * m
        ones_col = [0] * n

        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    ones_row[i] += 1
                    ones_col[j] += 1

        diff = [[0] * n for _ in range(m)]

        for i in range(m):
            for j in range(n):
                zeros_row = n - ones_row[i]
                zeros_col = m - ones_col[j]
                diff[i][j] = ones_row[i] + ones_col[j] - zeros_row - zeros_col

        return diff