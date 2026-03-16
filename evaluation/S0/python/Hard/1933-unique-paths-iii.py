# Source: https://leetcode.com/problems/unique-paths-iii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an m x n integer array grid where grid[i][j] could be:
#
#
# 	1 representing the starting square. There is exactly one starting square.
# 	2 representing the ending square. There is exactly one ending square.
# 	0 representing empty squares we can walk over.
# 	-1 representing obstacles that we cannot walk over.
#
#
# Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.
#
# Example:
# Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
# Output: 2
# Explanation: We have the following two paths: 
# 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
# 2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 20
# 	1 <= m * n <= 20
# 	-1 <= grid[i][j] <= 2
# 	There is exactly one starting cell and one ending cell.
#

class Solution(object):
    def uniquePathsIII(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        rows, cols = len(grid), len(grid[0])
        empty_count = 0
        start_x = start_y = end_x = end_y = 0
        
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 0:
                    empty_count += 1
                elif grid[r][c] == 1:
                    start_x, start_y = r, c
                elif grid[r][c] == 2:
                    end_x, end_y = r, c
        
        def backtrack(x, y, remain):
            if x == end_x and y == end_y:
                return 1 if remain == -1 else 0
            
            temp, grid[x][y] = grid[x][y], -4
            paths = 0
            
            for dx, dy in [(-1,0), (1,0), (0,-1), (0,1)]:
                nx, ny = x + dx, y + dy
                if 0 <= nx < rows and 0 <= ny < cols and grid[nx][ny] >= 0:
                    paths += backtrack(nx, ny, remain - 1)
            
            grid[x][y] = temp
            return paths
        
        return backtrack(start_x, start_y, empty_count)