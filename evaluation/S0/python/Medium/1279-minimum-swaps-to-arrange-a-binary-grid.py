# Source: https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/   |   Difficulty: Medium
#
# Problem Description:
# Given an n x n binary grid, in one step you can choose two adjacent rows of the grid and swap them.
#
# A grid is said to be valid if all the cells above the main diagonal are zeros.
#
# Return the minimum number of steps needed to make the grid valid, or -1 if the grid cannot be valid.
#
# The main diagonal of a grid is the diagonal that starts at cell (1, 1) and ends at cell (n, n).
#
# Example:
# Input: grid = [[0,0,1],[1,1,0],[1,0,0]]
# Output: 3
#
# Constraints:
# n == grid.length == grid[i].length
# 	1 <= n <= 200
# 	grid[i][j] is either 0 or 1
#

class Solution(object):
    def minSwaps(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        trailing_zeros = []
        
        for row in grid:
            count = 0
            for val in reversed(row):
                if val == 0:
                    count += 1
                else:
                    break
            trailing_zeros.append(count)
        
        swaps = 0
        
        for i in range(n):
            required_zeros = n - 1 - i
            if trailing_zeros[i] >= required_zeros:
                continue
            
            j = i + 1
            while j < n and trailing_zeros[j] < required_zeros:
                j += 1
            
            if j == n:
                return -1
            
            while j > i:
                trailing_zeros[j], trailing_zeros[j - 1] = trailing_zeros[j - 1], trailing_zeros[j]
                swaps += 1
                j -= 1
        
        return swaps