# Source: https://leetcode.com/problems/fill-a-special-grid/   |   Difficulty: Medium
#
# Problem Description:
# You are given a non-negative integer n representing a 2n x 2n grid. You must fill the grid with integers from 0 to 22n - 1 to make it special. A grid is special if it satisfies all the following conditions:
#
#
# 	All numbers in the top-right quadrant are smaller than those in the bottom-right quadrant.
# 	All numbers in the bottom-right quadrant are smaller than those in the bottom-left quadrant.
# 	All numbers in the bottom-left quadrant are smaller than those in the top-left quadrant.
# 	Each of its quadrants is also a special grid.
#
#
# Return the special 2n x 2n grid.
#
# Note: Any 1x1 grid is special.
#
# Example:
# Input: n = 0
#
# Output: [[0]]
#
# Explanation:
#
# The only number that can be placed is 0, and there is only one possible position in the grid.
#
# Constraints:
# 0 <= n <= 10
#

class Solution(object):
    def specialGrid(self, n):
        """
        :type n: int
        :rtype: List[List[int]]
        """
        size = 2 ** n
        grid = [[0] * size for _ in range(size)]
        
        def fill_grid(x, y, length, start):
            if length == 1:
                grid[x][y] = start
                return
            
            half = length // 2
            fill_grid(x, y + half, half, start)  # Top-right
            fill_grid(x + half, y + half, half, start + half * half)  # Bottom-right
            fill_grid(x + half, y, half, start + 2 * half * half)  # Bottom-left
            fill_grid(x, y, half, start + 3 * half * half)  # Top-left
        
        fill_grid(0, 0, size, 0)
        return grid