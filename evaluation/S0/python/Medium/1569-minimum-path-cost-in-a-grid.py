# Source: https://leetcode.com/problems/minimum-path-cost-in-a-grid/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed m x n integer matrix grid consisting of distinct integers from 0 to m * n - 1. You can move in this matrix from a cell to any other cell in the next row. That is, if you are in cell (x, y) such that x < m - 1, you can move to any of the cells (x + 1, 0), (x + 1, 1), ..., (x + 1, n - 1). Note that it is not possible to move from cells in the last row.
#
# Each possible move has a cost given by a 0-indexed 2D array moveCost of size (m * n) x n, where moveCost[i][j] is the cost of moving from a cell with value i to a cell in column j of the next row. The cost of moving from cells in the last row of grid can be ignored.
#
# The cost of a path in grid is the sum of all values of cells visited plus the sum of costs of all the moves made. Return the minimum cost of a path that starts from any cell in the first row and ends at any cell in the last row.
#
# Example:
# Input: grid = [[5,3],[4,0],[2,1]], moveCost = [[9,8],[1,5],[10,12],[18,6],[2,4],[14,3]]
# Output: 17
# Explanation: The path with the minimum possible cost is the path 5 -> 0 -> 1.
# - The sum of the values of cells visited is 5 + 0 + 1 = 6.
# - The cost of moving from 5 to 0 is 3.
# - The cost of moving from 0 to 1 is 8.
# So the total cost of the path is 6 + 3 + 8 = 17.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	2 <= m, n <= 50
# 	grid consists of distinct integers from 0 to m * n - 1.
# 	moveCost.length == m * n
# 	moveCost[i].length == n
# 	1 <= moveCost[i][j] <= 100
#

class Solution(object):
    def minPathCost(self, grid, moveCost):
        """
        :type grid: List[List[int]]
        :type moveCost: List[List[int]]
        :rtype: int
        """
        m = len(grid)
        n = len(grid[0])
        
        # dp[i][j] 表示到达第 i 行第 j 列的最小路径代价
        dp = [[float('inf')] * n for _ in range(m)]
        
        # 初始化第一行的代价为对应的格子值
        for j in range(n):
            dp[0][j] = grid[0][j]
        
        # 计算每一行的最小路径代价
        for i in range(1, m):
            for j in range(n):
                for k in range(n):
                    cost = dp[i-1][k] + moveCost[grid[i-1][k]][j] + grid[i][j]
                    dp[i][j] = min(dp[i][j], cost)
        
        # 返回最后一行的最小路径代价
        return min(dp[m-1])