# Source: https://leetcode.com/problems/minimum-moves-to-move-a-box-to-their-target-location/   |   Difficulty: Hard
#
# Problem Description:
# A storekeeper is a game in which the player pushes boxes around in a warehouse trying to get them to target locations.
#
# The game is represented by an m x n grid of characters grid where each element is a wall, floor, or box.
#
# Your task is to move the box 'B' to the target position 'T' under the following rules:
#
#
# 	The character 'S' represents the player. The player can move up, down, left, right in grid if it is a floor (empty cell).
# 	The character '.' represents the floor which means a free cell to walk.
# 	The character '#' represents the wall which means an obstacle (impossible to walk there).
# 	There is only one box 'B' and one target cell 'T' in the grid.
# 	The box can be moved to an adjacent free cell by standing next to the box and then moving in the direction of the box. This is a push.
# 	The player cannot walk through the box.
#
#
# Return the minimum number of pushes to move the box to the target. If there is no way to reach the target, return -1.
#
# Example:
# Input: grid = [["#","#","#","#","#","#"],
#                ["#","T","#","#","#","#"],
#                ["#",".",".","B",".","#"],
#                ["#",".","#","#",".","#"],
#                ["#",".",".",".","S","#"],
#                ["#","#","#","#","#","#"]]
# Output: 3
# Explanation: We return only the number of times the box is pushed.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 20
# 	grid contains only characters '.', '#', 'S', 'T', or 'B'.
# 	There is only one character 'S', 'B', and 'T' in the grid.
#

class Solution(object):
    def minPushBox(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: int
        """
        from collections import deque

        m, n = len(grid), len(grid[0])
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

        def is_valid(x, y):
            return 0 <= x < m and 0 <= y < n and grid[x][y] != '#'

        def can_reach(sx, sy, tx, ty, bx, by):
            visited = set()
            queue = deque([(sx, sy)])
            visited.add((sx, sy))

            while queue:
                x, y = queue.popleft()
                if (x, y) == (tx, ty):
                    return True
                for dx, dy in directions:
                    nx, ny = x + dx, y + dy
                    if is_valid(nx, ny) and (nx, ny) not in visited and (nx, ny) != (bx, by):
                        visited.add((nx, ny))
                        queue.append((nx, ny))
            return False

        for i in range(m):
            for j in range(n):
                if grid[i][j] == 'S':
                    sx, sy = i, j
                elif grid[i][j] == 'B':
                    bx, by = i, j
                elif grid[i][j] == 'T':
                    tx, ty = i, j

        queue = deque([(bx, by, sx, sy, 0)])
        visited = set()
        visited.add((bx, by, sx, sy))

        while queue:
            bx, by, sx, sy, pushes = queue.popleft()
            if (bx, by) == (tx, ty):
                return pushes

            for dx, dy in directions:
                nbx, nby = bx + dx, by + dy
                psx, psy = bx - dx, by - dy

                if is_valid(nbx, nby) and is_valid(psx, psy):
                    if can_reach(sx, sy, psx, psy, bx, by):
                        if (nbx, nby, bx, by) not in visited:
                            visited.add((nbx, nby, bx, by))
                            queue.append((nbx, nby, bx, by, pushes + 1))

        return -1