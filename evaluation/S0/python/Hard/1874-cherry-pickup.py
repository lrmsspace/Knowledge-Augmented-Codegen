# Source: https://leetcode.com/problems/cherry-pickup/   |   Difficulty: Hard
#
# Problem Description:
# You are given an n x n grid representing a field of cherries, each cell is one of three possible integers.
#
#
# 	0 means the cell is empty, so you can pass through,
# 	1 means the cell contains a cherry that you can pick up and pass through, or
# 	-1 means the cell contains a thorn that blocks your way.
#
#
# Return the maximum number of cherries you can collect by following the rules below:
#
#
# 	Starting at the position (0, 0) and reaching (n - 1, n - 1) by moving right or down through valid path cells (cells with value 0 or 1).
# 	After reaching (n - 1, n - 1), returning to (0, 0) by moving left or up through valid path cells.
# 	When passing through a path cell containing a cherry, you pick it up, and the cell becomes an empty cell 0.
# 	If there is no valid path between (0, 0) and (n - 1, n - 1), then no cherries can be collected.
#
# Example:
# Input: grid = [[0,1,-1],[1,0,-1],[1,1,1]]
# Output: 5
# Explanation: The player started at (0, 0) and went down, down, right right to reach (2, 2).
# 4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
# Then, the player went left, up, up, left to return home, picking up one more cherry.
# The total number of cherries picked up is 5, and this is the maximum possible.
#
# Constraints:
# n == grid.length
# 	n == grid[i].length
# 	1 <= n <= 50
# 	grid[i][j] is -1, 0, or 1.
# 	grid[0][0] != -1
# 	grid[n - 1][n - 1] != -1
#

class Solution(object):
    def cherryPickup(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        dp = [[[-1] * n for _ in range(n)] for _ in range(n)]
        dp[0][0][0] = grid[0][0]

        for t in range(1, 2 * n - 1):
            for x1 in range(max(0, t - (n - 1)), min(n, t + 1)):
                y1 = t - x1
                if y1 < 0 or y1 >= n or grid[x1][y1] == -1:
                    continue
                for x2 in range(max(0, t - (n - 1)), min(n, t + 1)):
                    y2 = t - x2
                    if y2 < 0 or y2 >= n or grid[x2][y2] == -1:
                        continue
                    val = grid[x1][y1]
                    if x1 != x2:
                        val += grid[x2][y2]
                    max_prev = -1
                    for dx1 in (-1, 0):
                        for dx2 in (-1, 0):
                            prev_x1, prev_y1 = x1 + dx1, y1 - (1 + dx1)
                            prev_x2, prev_y2 = x2 + dx2, y2 - (1 + dx2)
                            if 0 <= prev_x1 < n and 0 <= prev_y1 < n and 0 <= prev_x2 < n and 0 <= prev_y2 < n:
                                if dp[prev_x1][prev_x2][t - 1] != -1:
                                    max_prev = max(max_prev, dp[prev_x1][prev_x2][t - 1])
                    if max_prev != -1:
                        dp[x1][x2][t] = max_prev + val
        return max(0, dp[n - 1][n - 1][2 * n - 2])