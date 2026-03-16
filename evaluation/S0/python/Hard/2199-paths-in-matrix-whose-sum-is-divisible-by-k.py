# Source: https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed m x n integer matrix grid and an integer k. You are currently at position (0, 0) and you want to reach position (m - 1, n - 1) moving only down or right.
#
# Return the number of paths where the sum of the elements on the path is divisible by k. Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: grid = [[5,2,4],[3,0,5],[0,7,2]], k = 3
# Output: 2
# Explanation: There are two paths where the sum of the elements on the path is divisible by k.
# The first path highlighted in red has a sum of 5 + 2 + 4 + 5 + 2 = 18 which is divisible by 3.
# The second path highlighted in blue has a sum of 5 + 3 + 0 + 5 + 2 = 15 which is divisible by 3.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 5 * 104
# 	1 <= m * n <= 5 * 104
# 	0 <= grid[i][j] <= 100
# 	1 <= k <= 50
#

class Solution(object):
    def numberOfPaths(self, grid, k):
        """
        :type grid: List[List[int]]
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        m, n = len(grid), len(grid[0])
        dp = [[[0] * k for _ in range(n)] for _ in range(m)]
        dp[0][0][grid[0][0] % k] = 1
        
        for i in range(m):
            for j in range(n):
                for r in range(k):
                    if i > 0:
                        dp[i][j][(r + grid[i][j]) % k] = (dp[i][j][(r + grid[i][j]) % k] + dp[i-1][j][r]) % MOD
                    if j > 0:
                        dp[i][j][(r + grid[i][j]) % k] = (dp[i][j][(r + grid[i][j]) % k] + dp[i][j-1][r]) % MOD
        
        return dp[m-1][n-1][0]