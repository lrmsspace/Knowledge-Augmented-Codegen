# Source: https://leetcode.com/problems/minimum-path-sum/   |   Difficulty: Medium
#
# Problem Description:
# Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.
#
# Note: You can only move either down or right at any point in time.
#
# Example:
# Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
# Output: 7
# Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 200
# 	0 <= grid[i][j] <= 200
#

class Solution(object):
    def minPathSum(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        if not grid or not grid[0]:
            return 0
        
        m, n = len(grid), len(grid[0])
        
        # Create a 2D dp array to store the minimum path sums
        dp = [[0] * n for _ in range(m)]
        
        # Initialize the top-left corner
        dp[0][0] = grid[0][0]
        
        # Fill the first row
        for j in range(1, n):
            dp[0][j] = dp[0][j - 1] + grid[0][j]
        
        # Fill the first column
        for i in range(1, m):
            dp[i][0] = dp[i - 1][0] + grid[i][0]
        
        # Fill the rest of the dp array
        for i in range(1, m):
            for j in range(1, n):
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j]
        
        return dp[m - 1][n - 1]