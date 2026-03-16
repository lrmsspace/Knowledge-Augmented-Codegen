# Source: https://leetcode.com/problems/shift-2d-grid/   |   Difficulty: Easy
#
# Problem Description:
# Given a 2D grid of size m x n and an integer k. You need to shift the grid k times.
#
# In one shift operation:
#
#
# 	Element at grid[i][j] moves to grid[i][j + 1].
# 	Element at grid[i][n - 1] moves to grid[i + 1][0].
# 	Element at grid[m - 1][n - 1] moves to grid[0][0].
#
#
# Return the 2D grid after applying shift operation k times.
#
# Example:
# Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1
# Output: [[9,1,2],[3,4,5],[6,7,8]]
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m <= 50
# 	1 <= n <= 50
# 	-1000 <= grid[i][j] <= 1000
# 	0 <= k <= 100
#

class Solution(object):
    def shiftGrid(self, grid, k):
        """
        :type grid: List[List[int]]
        :type k: int
        :rtype: List[List[int]]
        """
        m = len(grid)
        n = len(grid[0])
        total = m * n
        k = k % total  # In case k is larger than total elements

        # Flatten the grid to a 1D list
        flat_list = [grid[i][j] for i in range(m) for j in range(n)]

        # Shift the flat list
        shifted_list = flat_list[-k:] + flat_list[:-k]

        # Reconstruct the 2D grid
        new_grid = []
        for i in range(m):
            new_grid.append(shifted_list[i*n:(i+1)*n])

        return new_grid