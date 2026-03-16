# Source: https://leetcode.com/problems/maximum-trailing-zeros-in-a-cornered-path/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D integer array grid of size m x n, where each cell contains a positive integer.
#
# A cornered path is defined as a set of adjacent cells with at most one turn. More specifically, the path should exclusively move either horizontally or vertically up to the turn (if there is one), without returning to a previously visited cell. After the turn, the path will then move exclusively in the alternate direction: move vertically if it moved horizontally, and vice versa, also without returning to a previously visited cell.
#
# The product of a path is defined as the product of all the values in the path.
#
# Return the maximum number of trailing zeros in the product of a cornered path found in grid.
#
# Note:
#
#
# 	Horizontal movement means moving in either the left or right direction.
# 	Vertical movement means moving in either the up or down direction.
#
# Example:
# Input: grid = [[23,17,15,3,20],[8,1,20,27,11],[9,4,6,2,21],[40,9,1,10,6],[22,7,4,5,3]]
# Output: 3
# Explanation: The grid on the left shows a valid cornered path.
# It has a product of 15 * 20 * 6 * 1 * 10 = 18000 which has 3 trailing zeros.
# It can be shown that this is the maximum trailing zeros in the product of a cornered path.
#
# The grid in the middle is not a cornered path as it has more than one turn.
# The grid on the right is not a cornered path as it requires a return to a previously visited cell.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 105
# 	1 <= m * n <= 105
# 	1 <= grid[i][j] <= 1000
#

class Solution(object):
    def maxTrailingZeros(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict

        def count_factors(num, factor):
            count = 0
            while num % factor == 0:
                num //= factor
                count += 1
            return count

        m, n = len(grid), len(grid[0])
        max_zeros = 0

        # Precompute the number of 2s and 5s in each cell
        twos = [[0] * n for _ in range(m)]
        fives = [[0] * n for _ in range(m)]

        for i in range(m):
            for j in range(n):
                twos[i][j] = count_factors(grid[i][j], 2)
                fives[i][j] = count_factors(grid[i][j], 5)

        # Prefix sums for rows and columns
        row_twos = [[0] * (n + 1) for _ in range(m)]
        row_fives = [[0] * (n + 1) for _ in range(m)]
        col_twos = [[0] * (m + 1) for _ in range(n)]
        col_fives = [[0] * (m + 1) for _ in range(n)]

        for i in range(m):
            for j in range(n):
                row_twos[i][j + 1] = row_twos[i][j] + twos[i][j]
                row_fives[i][j + 1] = row_fives[i][j] + fives[i][j]
                col_twos[j][i + 1] = col_twos[j][i] + twos[i][j]
                col_fives[j][i + 1] = col_fives[j][i] + fives[i][j]

        # Check all cornered paths
        for i in range(m):
            for j in range(n):
                # Up-Left
                up_twos = col_twos[j][i]
                up_fives = col_fives[j][i]
                left_twos = row_twos[i][j]
                left_fives = row_fives[i][j]
                total_twos = up_twos + left_twos + twos[i][j]
                total_fives = up_fives + left_fives + fives[i][j]
                max_zeros = max(max_