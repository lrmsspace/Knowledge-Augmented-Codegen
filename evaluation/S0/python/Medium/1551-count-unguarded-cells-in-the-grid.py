# Source: https://leetcode.com/problems/count-unguarded-cells-in-the-grid/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integers m and n representing a 0-indexed m x n grid. You are also given two 2D integer arrays guards and walls where guards[i] = [rowi, coli] and walls[j] = [rowj, colj] represent the positions of the ith guard and jth wall respectively.
#
# A guard can see every cell in the four cardinal directions (north, east, south, or west) starting from their position unless obstructed by a wall or another guard. A cell is guarded if there is at least one guard that can see it.
#
# Return the number of unoccupied cells that are not guarded.
#
# Example:
# Input: m = 4, n = 6, guards = [[0,0],[1,1],[2,3]], walls = [[0,1],[2,2],[1,4]]
# Output: 7
# Explanation: The guarded and unguarded cells are shown in red and green respectively in the above diagram.
# There are a total of 7 unguarded cells, so we return 7.
#
# Constraints:
# 1 <= m, n <= 105
# 	2 <= m * n <= 105
# 	1 <= guards.length, walls.length <= 5 * 104
# 	2 <= guards.length + walls.length <= m * n
# 	guards[i].length == walls[j].length == 2
# 	0 <= rowi, rowj < m
# 	0 <= coli, colj < n
# 	All the positions in guards and walls are unique.
#

class Solution(object):
    def countUnguarded(self, m, n, guards, walls):
        """
        :type m: int
        :type n: int
        :type guards: List[List[int]]
        :type walls: List[List[int]]
        :rtype: int
        """
        grid = [[0] * n for _ in range(m)]
        for r, c in walls:
            grid[r][c] = -1
        for r, c in guards:
            grid[r][c] = 1

        for r, c in guards:
            # Up
            for i in range(r - 1, -1, -1):
                if grid[i][c] == -1 or grid[i][c] == 1:
                    break
                grid[i][c] = 2
            # Down
            for i in range(r + 1, m):
                if grid[i][c] == -1 or grid[i][c] == 1:
                    break
                grid[i][c] = 2
            # Left
            for j in range(c - 1, -1, -1):
                if grid[r][j] == -1 or grid[r][j] == 1:
                    break
                grid[r][j] = 2
            # Right
            for j in range(c + 1, n):
                if grid[r][j] == -1 or grid[r][j] == 1:
                    break
                grid[r][j] = 2

        unguarded_count = 0
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 0:
                    unguarded_count += 1

        return unguarded_count