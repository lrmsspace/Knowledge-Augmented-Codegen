# Source: https://leetcode.com/problems/shortest-path-in-binary-matrix/   |   Difficulty: Medium
#
# Problem Description:
# Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.
#
# A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
#
#
# 	All the visited cells of the path are 0.
# 	All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
#
#
# The length of a clear path is the number of visited cells of this path.
#
# Example:
# Input: grid = [[0,1],[1,0]]
# Output: 2
#
# Constraints:
# n == grid.length
# 	n == grid[i].length
# 	1 <= n <= 100
# 	grid[i][j] is 0 or 1
#

class Solution(object):
    def shortestPathBinaryMatrix(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        if grid[0][0] != 0 or grid[n-1][n-1] != 0:
            return -1
        
        directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
        queue = [(0, 0, 1)]  # (row, col, path_length)
        visited = set((0, 0))
        
        while queue:
            r, c, length = queue.pop(0)
            if r == n-1 and c == n-1:
                return length
            
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < n and 0 <= nc < n and grid[nr][nc] == 0 and (nr, nc) not in visited:
                    visited.add((nr, nc))
                    queue.append((nr, nc, length + 1))
        
        return -1