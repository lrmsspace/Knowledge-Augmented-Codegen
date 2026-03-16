# Source: https://leetcode.com/problems/path-with-maximum-gold/   |   Difficulty: Medium
#
# Problem Description:
# In a gold mine grid of size m x n, each cell in this mine has an integer representing the amount of gold in that cell, 0 if it is empty.
#
# Return the maximum amount of gold you can collect under the conditions:
#
#
# 	Every time you are located in a cell you will collect all the gold in that cell.
# 	From your position, you can walk one step to the left, right, up, or down.
# 	You can't visit the same cell more than once.
# 	Never visit a cell with 0 gold.
# 	You can start and stop collecting gold from any position in the grid that has some gold.
#
# Example:
# Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
# Output: 24
# Explanation:
# [[0,6,0],
#  [5,8,7],
#  [0,9,0]]
# Path to get the maximum gold, 9 -> 8 -> 7.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 15
# 	0 <= grid[i][j] <= 100
# 	There are at most 25 cells containing gold.
#

class Solution(object):
    def getMaximumGold(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        rows, cols = len(grid), len(grid[0])
        max_gold = 0

        def dfs(r, c, current_gold):
            nonlocal max_gold
            if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] == 0:
                max_gold = max(max_gold, current_gold)
                return

            gold = grid[r][c]
            grid[r][c] = 0  # Mark as visited

            # Explore all four directions
            dfs(r + 1, c, current_gold + gold)
            dfs(r - 1, c, current_gold + gold)
            dfs(r, c + 1, current_gold + gold)
            dfs(r, c - 1, current_gold + gold)

            grid[r][c] = gold  # Backtrack

        for i in range(rows):
            for j in range(cols):
                if grid[i][j] > 0:
                    dfs(i, j, 0)

        return max_gold