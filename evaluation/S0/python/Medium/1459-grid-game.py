# Source: https://leetcode.com/problems/grid-game/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed 2D array grid of size 2 x n, where grid[r][c] represents the number of points at position (r, c) on the matrix. Two robots are playing a game on this matrix.
#
# Both robots initially start at (0, 0) and want to reach (1, n-1). Each robot may only move to the right ((r, c) to (r, c + 1)) or down ((r, c) to (r + 1, c)).
#
# At the start of the game, the first robot moves from (0, 0) to (1, n-1), collecting all the points from the cells on its path. For all cells (r, c) traversed on the path, grid[r][c] is set to 0. Then, the second robot moves from (0, 0) to (1, n-1), collecting the points on its path. Note that their paths may intersect with one another.
#
# The first robot wants to minimize the number of points collected by the second robot. In contrast, the second robot wants to maximize the number of points it collects. If both robots play optimally, return the number of points collected by the second robot.
#
# Example:
# Input: grid = [[2,5,4],[1,5,1]]
# Output: 4
# Explanation: The optimal path taken by the first robot is shown in red, and the optimal path taken by the second robot is shown in blue.
# The cells visited by the first robot are set to 0.
# The second robot will collect 0 + 0 + 4 + 0 = 4 points.
#
# Constraints:
# grid.length == 2
# 	n == grid[r].length
# 	1 <= n <= 5 * 104
# 	1 <= grid[r][c] <= 105
#

class Solution(object):
    def gridGame(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid[0])
        top_prefix_sum = [0] * (n + 1)
        bottom_prefix_sum = [0] * (n + 1)

        for i in range(n):
            top_prefix_sum[i + 1] = top_prefix_sum[i] + grid[0][i]
            bottom_prefix_sum[i + 1] = bottom_prefix_sum[i] + grid[1][i]

        min_second_robot_points = float('inf')

        for col in range(n):
            points_above = top_prefix_sum[n] - top_prefix_sum[col + 1]
            points_below = bottom_prefix_sum[col]
            second_robot_points = max(points_above, points_below)
            min_second_robot_points = min(min_second_robot_points, second_robot_points)

        return min_second_robot_points