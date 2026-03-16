# Source: https://leetcode.com/problems/grid-teleportation-traversal/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D character grid matrix of size m x n, represented as an array of strings, where matrix[i][j] represents the cell at the intersection of the ith row and jth column. Each cell is one of the following:
#
#
# 	'.' representing an empty cell.
# 	'#' representing an obstacle.
# 	An uppercase letter ('A'-'Z') representing a teleportation portal.
#
#
# You start at the top-left cell (0, 0), and your goal is to reach the bottom-right cell (m - 1, n - 1). You can move from the current cell to any adjacent cell (up, down, left, right) as long as the destination cell is within the grid bounds and is not an obstacle.
#
# If you step on a cell containing a portal letter and you haven't used that portal letter before, you may instantly teleport to any other cell in the grid with the same letter. This teleportation does not count as a move, but each portal letter can be used at most once during your journey.
#
# Return the minimum number of moves required to reach the bottom-right cell. If it is not possible to reach the destination, return -1.
#
# Example:
# Input: matrix = ["A..",".A.","..."]
#
# Output: 2
#
# Explanation:
#
#
#
#
# 	Before the first move, teleport from (0, 0) to (1, 1).
# 	In the first move, move from (1, 1) to (1, 2).
# 	In the second move, move from (1, 2) to (2, 2).
#
# Constraints:
# 1 <= m == matrix.length <= 103
# 	1 <= n == matrix[i].length <= 103
# 	matrix[i][j] is either '#', '.', or an uppercase English letter.
# 	matrix[0][0] is not an obstacle.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minMoves(self, matrix):
        """
        :type matrix: List[str]
        :rtype: int
        """
        from collections import deque, defaultdict

        m, n = len(matrix), len(matrix[0])
        portals = defaultdict(list)

        # Collect portal positions
        for i in range(m):
            for j in range(n):
                if matrix[i][j].isalpha():
                    portals[matrix[i][j]].append((i, j))

        visited = set()
        queue = deque([(0, 0, 0)])  # (x, y, moves)
        visited.add((0, 0))

        while queue:
            x, y, moves = queue.popleft()

            if (x, y) == (m - 1, n - 1):
                return moves

            # Move to adjacent cells
            for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and matrix[nx][ny] != '#' and (nx, ny) not in visited:
                    visited.add((nx, ny))
                    queue.append((nx, ny, moves + 1))

            # Teleportation
            if matrix[x][y].isalpha():
                portal_char = matrix[x][y]
                for px, py in portals[portal_char]:
                    if (px, py) != (x, y) and (px, py) not in visited:
                        visited.add((px, py))
                        queue.append((px, py, moves))  # Teleportation does not count as a move
                portals[portal_char] = []  # Mark this portal as used

        return -1