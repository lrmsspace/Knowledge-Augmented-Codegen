# Source: https://leetcode.com/problems/count-paths-with-the-given-xor-value/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D integer array grid with size m x n. You are also given an integer k.
#
# Your task is to calculate the number of paths you can take from the top-left cell (0, 0) to the bottom-right cell (m - 1, n - 1) satisfying the following constraints:
#
#
# 	You can either move to the right or down. Formally, from the cell (i, j) you may move to the cell (i, j + 1) or to the cell (i + 1, j) if the target cell exists.
# 	The XOR of all the numbers on the path must be equal to k.
#
#
# Return the total number of such paths.
#
# Since the answer can be very large, return the result modulo 109 + 7.
#
# Example:
# Input: grid = [[2, 1, 5], [7, 10, 0], [12, 6, 4]], k = 11
#
# Output: 3
#
# Explanation: 
#
# The 3 paths are:
#
#
# 	(0, 0) → (1, 0) → (2, 0) → (2, 1) → (2, 2)
# 	(0, 0) → (1, 0) → (1, 1) → (1, 2) → (2, 2)
# 	(0, 0) → (0, 1) → (1, 1) → (2, 1) → (2, 2)
#
# Constraints:
# 1 <= m == grid.length <= 300
# 	1 <= n == grid[r].length <= 300
# 	0 <= grid[r][c] < 16
# 	0 <= k < 16
#

class Solution(object):
    def countPathsWithXorValue(self, grid, k):
        """
        :type grid: List[List[int]]
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        m, n = len(grid), len(grid[0])
        # dp[i][j][x] 表示到达 (i, j) 位置时，路径异或和为 x 的路径数量
        dp = [[[0] * 16 for _ in range(n)] for _ in range(m)]
        dp[0][0][grid[0][0]] = 1

        for i in range(m):
            for j in range(n):
                for x in range(16):
                    if i > 0:
                        new_xor = x ^ grid[i][j]
                        dp[i][j][new_xor] = (dp[i][j][new_xor] + dp[i-1][j][x]) % MOD
                    if j > 0:
                        new_xor = x ^ grid[i][j]
                        dp[i][j][new_xor] = (dp[i][j][new_xor] + dp[i][j-1][x]) % MOD

        return dp[m-1][n-1][k]