# Source: https://leetcode.com/problems/minimum-moves-to-reach-target-with-rotations/   |   Difficulty: Hard
#
# Problem Description:
# In an n*n grid, there is a snake that spans 2 cells and starts moving from the top left corner at (0, 0) and (0, 1). The grid has empty cells represented by zeros and blocked cells represented by ones. The snake wants to reach the lower right corner at (n-1, n-2) and (n-1, n-1).
#
# In one move the snake can:
#
#
# 	Move one cell to the right if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
# 	Move down one cell if there are no blocked cells there. This move keeps the horizontal/vertical position of the snake as it is.
# 	Rotate clockwise if it's in a horizontal position and the two cells under it are both empty. In that case the snake moves from (r, c) and (r, c+1) to (r, c) and (r+1, c).
# 	
# 	Rotate counterclockwise if it's in a vertical position and the two cells to its right are both empty. In that case the snake moves from (r, c) and (r+1, c) to (r, c) and (r, c+1).
# 	
#
#
# Return the minimum number of moves to reach the target.
#
# If there is no way to reach the target, return -1.
#
# Example:
# Input: grid = [[0,0,0,0,0,1],
#                [1,1,0,0,1,0],
#                [0,0,0,0,1,1],
#                [0,0,1,0,1,0],
#                [0,1,1,0,0,0],
#                [0,1,1,0,0,0]]
# Output: 11
# Explanation:
# One possible solution is [right, right, rotate clockwise, right, down, down, down, down, rotate counterclockwise, right, down].
#
# Constraints:
# 2 <= n <= 100
# 	0 <= grid[i][j] <= 1
# 	It is guaranteed that the snake starts at empty cells.
#

class Solution(object):
    def minimumMoves(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        from collections import deque

        n = len(grid)
        target = (n - 1, n - 2, 0)  # (row, col, orientation)

        directions = [(0, 1), (1, 0)]  # right, down
        visited = set()
        queue = deque([ (0, 0, 0, 0) ])  # (row, col, orientation, moves)
        visited.add((0, 0, 0))

        while queue:
            r, c, orientation, moves = queue.popleft()

            if (r, c, orientation) == target:
                return moves

            # Move right or down
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if orientation == 0:  # horizontal
                    if dr == 0 and nc + 1 < n and grid[nr][nc] == 0 and grid[nr][nc + 1] == 0:
                        if (nr, nc, orientation) not in visited:
                            visited.add((nr, nc, orientation))
                            queue.append((nr, nc, orientation, moves + 1))
                    elif dr == 1 and nr < n and grid[nr][nc] == 0 and grid[nr][nc + 1] == 0:
                        if (nr, nc, orientation) not in visited:
                            visited.add((nr, nc, orientation))
                            queue.append((nr, nc, orientation, moves + 1))
                else:  # vertical
                    if dr == 0 and nc < n and grid[nr][nc] == 0 and grid[nr + 1][nc] == 0:
                        if (nr, nc, orientation) not in visited:
                            visited.add((nr, nc, orientation))
                            queue.append((nr, nc, orientation, moves + 1))
                    elif dr == 1 and nr + 1 < n and grid[nr][nc] == 0 and grid[nr + 1][nc] == 0:
                        if (nr, nc, orientation) not in visited:
                            visited.add((nr, nc, orientation))
                            queue.append((nr, nc, orientation, moves + 1))

            # Rotate
            if orientation == 0:  # horizontal to vertical
                if r + 1 < n and grid[r + 1][c] == 0 and grid[r + 1][c + 1] == 0:
                    if (r, c, 1) not in visited:
                        visited.add((r, c, 1))
                        queue.append((r, c, 1, moves + 1))
            else:  # vertical to horizontal
                if c + 1 < n and grid[r][c + 1] == 0 and grid[r + 1][c + 1] == 0:
                    if (r, c, 0) not in visited:
                        visited.add((r, c, 0))
                        queue.append((r, c, 0, moves + 1))
        return -1   