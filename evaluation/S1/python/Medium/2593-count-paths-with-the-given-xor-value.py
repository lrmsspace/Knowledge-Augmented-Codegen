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
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countPathsWithXorValue(self, grid, k):
        """
        :type grid: List[List[int]]
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        m, n = len(grid), len(grid[0])
        from collections import defaultdict

        # dp[i][j] will be a dictionary where key is the XOR value and value is the count of paths
        dp = [[defaultdict(int) for _ in range(n)] for _ in range(m)]
        dp[0][0][grid[0][0]] = 1

        for i in range(m):
            for j in range(n):
                if i == 0 and j == 0:
                    continue
                for xor_val, count in dp[i-1][j].items() if i > 0 else []:
                    new_xor = xor_val ^ grid[i][j]
                    dp[i][j][new_xor] = (dp[i][j][new_xor] + count) % MOD
                for xor_val, count in dp[i][j-1].items() if j > 0 else []:
                    new_xor = xor_val ^ grid[i][j]
                    dp[i][j][new_xor] = (dp[i][j][new_xor] + count) % MOD

        return dp[m-1][n-1][k] % MOD