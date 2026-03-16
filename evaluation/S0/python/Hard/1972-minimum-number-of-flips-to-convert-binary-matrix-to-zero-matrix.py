# Source: https://leetcode.com/problems/minimum-number-of-flips-to-convert-binary-matrix-to-zero-matrix/   |   Difficulty: Hard
#
# Problem Description:
# Given a m x n binary matrix mat. In one step, you can choose one cell and flip it and all the four neighbors of it if they exist (Flip is changing 1 to 0 and 0 to 1). A pair of cells are called neighbors if they share one edge.
#
# Return the minimum number of steps required to convert mat to a zero matrix or -1 if you cannot.
#
# A binary matrix is a matrix with all cells equal to 0 or 1 only.
#
# A zero matrix is a matrix with all cells equal to 0.
#
# Example:
# Input: mat = [[0,0],[0,1]]
# Output: 3
# Explanation: One possible solution is to flip (1, 0) then (0, 1) and finally (1, 1) as shown.
#
# Constraints:
# m == mat.length
# 	n == mat[i].length
# 	1 <= m, n <= 3
# 	mat[i][j] is either 0 or 1.
#

class Solution(object):
    def minFlips(self, mat):
        """
        :type mat: List[List[int]]
        :rtype: int
        """
        from collections import deque

        m, n = len(mat), len(mat[0])
        target = 0
        start = 0

        for i in range(m):
            for j in range(n):
                if mat[i][j] == 1:
                    start |= (1 << (i * n + j))

        def get_neighbors(state):
            neighbors = []
            for i in range(m):
                for j in range(n):
                    new_state = state
                    for dx, dy in [(0, 0), (1, 0), (-1, 0), (0, 1), (0, -1)]:
                        x, y = i + dx, j + dy
                        if 0 <= x < m and 0 <= y < n:
                            new_state ^= (1 << (x * n + y))
                    neighbors.append(new_state)
            return neighbors

        queue = deque([(start, 0)])
        visited = {start}

        while queue:
            state, steps = queue.popleft()
            if state == target:
                return steps
            for neighbor in get_neighbors(state):
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append((neighbor, steps + 1))

        return -1