# Source: https://leetcode.com/problems/out-of-boundary-paths/   |   Difficulty: Medium
#
# Problem Description:
# There is an m x n grid with a ball. The ball is initially at the position [startRow, startColumn]. You are allowed to move the ball to one of the four adjacent cells in the grid (possibly out of the grid crossing the grid boundary). You can apply at most maxMove moves to the ball.
#
# Given the five integers m, n, maxMove, startRow, startColumn, return the number of paths to move the ball out of the grid boundary. Since the answer can be very large, return it modulo 109 + 7.
#
# Example:
# Input: m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
# Output: 6
#
# Constraints:
# 1 <= m, n <= 50
# 	0 <= maxMove <= 50
# 	0 <= startRow < m
# 	0 <= startColumn < n
#

class Solution(object):
    def findPaths(self, m, n, maxMove, startRow, startColumn):
        """
        :type m: int
        :type n: int
        :type maxMove: int
        :type startRow: int
        :type startColumn: int
        :rtype: int
        """
        MOD = 10**9 + 7
        dp = [[[0] * n for _ in range(m)] for _ in range(maxMove + 1)]
        
        for move in range(1, maxMove + 1):
            for i in range(m):
                for j in range(n):
                    dp[move][i][j] = (
                        (dp[move - 1][i - 1][j] if i > 0 else 1) +
                        (dp[move - 1][i + 1][j] if i < m - 1 else 1) +
                        (dp[move - 1][i][j - 1] if j > 0 else 1) +
                        (dp[move - 1][i][j + 1] if j < n - 1 else 1)
                    ) % MOD
        
        return dp[maxMove][startRow][startColumn]