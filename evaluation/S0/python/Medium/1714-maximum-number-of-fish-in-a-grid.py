# Source: https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed 2D matrix grid of size m x n, where (r, c) represents:
#
#
# 	A land cell if grid[r][c] = 0, or
# 	A water cell containing grid[r][c] fish, if grid[r][c] > 0.
#
#
# A fisher can start at any water cell (r, c) and can do the following operations any number of times:
#
#
# 	Catch all the fish at cell (r, c), or
# 	Move to any adjacent water cell.
#
#
# Return the maximum number of fish the fisher can catch if he chooses his starting cell optimally, or 0 if no water cell exists.
#
# An adjacent cell of the cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) or (r - 1, c) if it exists.
#
# Example:
# Input: grid = [[0,2,1,0],[4,0,0,3],[1,0,0,4],[0,3,2,0]]
# Output: 7
# Explanation: The fisher can start at cell (1,3) and collect 3 fish, then move to cell (2,3) and collect 4 fish.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 10
# 	0 <= grid[i][j] <= 10
#

class Solution(object):
    def findMaxFish(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        rows, cols = len(grid), len(grid[0])
        visited = [[False for _ in range(cols)] for _ in range(rows)]
        
        def dfs(r, c):
            if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] == 0 or visited[r][c]:
                return 0
            
            visited[r][c] = True
            fish_count = grid[r][c]
            
            # Explore all four directions
            fish_count += dfs(r + 1, c)
            fish_count += dfs(r - 1, c)
            fish_count += dfs(r, c + 1)
            fish_count += dfs(r, c - 1)
            
            return fish_count
        
        max_fish = 0
        
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] > 0 and not visited[r][c]:
                    max_fish = max(max_fish, dfs(r, c))
        
        return max_fish