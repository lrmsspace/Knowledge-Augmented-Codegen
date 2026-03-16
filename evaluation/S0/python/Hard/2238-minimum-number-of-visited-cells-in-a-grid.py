# Source: https://leetcode.com/problems/minimum-number-of-visited-cells-in-a-grid/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed m x n integer matrix grid. Your initial position is at the top-left cell (0, 0).
#
# Starting from the cell (i, j), you can move to one of the following cells:
#
#
# 	Cells (i, k) with j < k <= grid[i][j] + j (rightward movement), or
# 	Cells (k, j) with i < k <= grid[i][j] + i (downward movement).
#
#
# Return the minimum number of cells you need to visit to reach the bottom-right cell (m - 1, n - 1). If there is no valid path, return -1.
#
# Example:
# Input: grid = [[3,4,2,1],[4,2,3,1],[2,1,0,0],[2,4,0,0]]
# Output: 4
# Explanation: The image above shows one of the paths that visits exactly 4 cells.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 105
# 	1 <= m * n <= 105
# 	0 <= grid[i][j] < m * n
# 	grid[m - 1][n - 1] == 0
#

class Solution(object):
    def minimumVisitedCells(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        from collections import deque
        import bisect

        m, n = len(grid), len(grid[0])
        row_sets = [list(range(n)) for _ in range(m)]
        col_sets = [list(range(m)) for _ in range(n)]

        queue = deque([(0, 0, 1)])  # (i, j, steps)
        visited = set((0, 0))

        while queue:
            i, j, steps = queue.popleft()
            if i == m - 1 and j == n - 1:
                return steps

            # Rightward movement
            max_right = min(n - 1, j + grid[i][j])
            row = row_sets[i]
            idx = bisect.bisect_right(row, j)
            while idx < len(row) and row[idx] <= max_right:
                nj = row[idx]
                if (i, nj) not in visited:
                    visited.add((i, nj))
                    queue.append((i, nj, steps + 1))
                idx += 1
            row_sets[i] = row[:bisect.bisect_right(row, max_right)]

            # Downward movement
            max_down = min(m - 1, i + grid[i][j])
            col = col_sets[j]
            idx = bisect.bisect_right(col, i)
            while idx < len(col) and col[idx] <= max_down:
                ni = col[idx]
                if (ni, j) not in visited:
                    visited.add((ni, j))
                    queue.append((ni, j, steps + 1))
                idx += 1
            col_sets[j] = col[:bisect.bisect_right(col, max_down)]

        return -1