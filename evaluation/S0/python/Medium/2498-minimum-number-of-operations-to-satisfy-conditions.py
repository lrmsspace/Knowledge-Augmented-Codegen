# Source: https://leetcode.com/problems/minimum-number-of-operations-to-satisfy-conditions/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D matrix grid of size m x n. In one operation, you can change the value of any cell to any non-negative number. You need to perform some operations such that each cell grid[i][j] is:
#
#
# 	Equal to the cell below it, i.e. grid[i][j] == grid[i + 1][j] (if it exists).
# 	Different from the cell to its right, i.e. grid[i][j] != grid[i][j + 1] (if it exists).
#
#
# Return the minimum number of operations needed.
#
# Example:
# Input: grid = [[1,0,2],[1,0,2]]
#
# Output: 0
#
# Explanation:
#
#
#
# All the cells in the matrix already satisfy the properties.
#
# Constraints:
# 1 <= n, m <= 1000
# 	0 <= grid[i][j] <= 9
#

class Solution(object):
    def minimumOperations(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        dp = [[float('inf')] * n for _ in range(m)]
        
        for j in range(n):
            dp[m-1][j] = 0
        
        for i in range(m-2, -1, -1):
            for j in range(n):
                for k in range(10):
                    cost = 0 if grid[i][j] == k else 1
                    for nj in range(n):
                        if j != nj:
                            if grid[i][j] == grid[i][nj]:
                                cost += 1
                    dp[i][j] = min(dp[i][j], dp[i+1][j] + cost)
        
        return min(dp[0])