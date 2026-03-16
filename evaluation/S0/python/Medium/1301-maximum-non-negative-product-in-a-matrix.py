# Source: https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/   |   Difficulty: Medium
#
# Problem Description:
# You are given a m x n matrix grid. Initially, you are located at the top-left corner (0, 0), and in each step, you can only move right or down in the matrix.
#
# Among all possible paths starting from the top-left corner (0, 0) and ending in the bottom-right corner (m - 1, n - 1), find the path with the maximum non-negative product. The product of a path is the product of all integers in the grid cells visited along the path.
#
# Return the maximum non-negative product modulo 109 + 7. If the maximum product is negative, return -1.
#
# Notice that the modulo is performed after getting the maximum product.
#
# Example:
# Input: grid = [[-1,-2,-3],[-2,-3,-3],[-3,-3,-2]]
# Output: -1
# Explanation: It is not possible to get non-negative product in the path from (0, 0) to (2, 2), so return -1.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 15
# 	-4 <= grid[i][j] <= 4
#

class Solution(object):
    def maxProductPath(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        MOD = 10**9 + 7
        m, n = len(grid), len(grid[0])
        
        max_dp = [[0] * n for _ in range(m)]
        min_dp = [[0] * n for _ in range(m)]
        
        max_dp[0][0] = min_dp[0][0] = grid[0][0]
        
        for i in range(m):
            for j in range(n):
                if i == 0 and j == 0:
                    continue
                
                if grid[i][j] >= 0:
                    if i > 0:
                        max_dp[i][j] = max_dp[i-1][j] * grid[i][j]
                        min_dp[i][j] = min_dp[i-1][j] * grid[i][j]
                    if j > 0:
                        max_dp[i][j] = max(max_dp[i][j], max_dp[i][j-1] * grid[i][j])
                        min_dp[i][j] = min(min_dp[i][j], min_dp[i][j-1] * grid[i][j])
                else:
                    if i > 0:
                        max_dp[i][j] = min_dp[i-1][j] * grid[i][j]
                        min_dp[i][j] = max_dp[i-1][j] * grid[i][j]
                    if j > 0:
                        max_dp[i][j] = max(max_dp[i][j], min_dp[i][j-1] * grid[i][j])
                        min_dp[i][j] = min(min_dp[i][j], max_dp[i][j-1] * grid[i][j])
        
        return max_dp[m-1][n-1] % MOD if max_dp[m-1][n-1] >= 0 else -1