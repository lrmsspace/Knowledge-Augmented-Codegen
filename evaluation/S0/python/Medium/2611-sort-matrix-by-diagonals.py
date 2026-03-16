# Source: https://leetcode.com/problems/sort-matrix-by-diagonals/   |   Difficulty: Medium
#
# Problem Description:
# You are given an n x n square matrix of integers grid. Return the matrix such that:
#
#
# 	The diagonals in the bottom-left triangle (including the middle diagonal) are sorted in non-increasing order.
# 	The diagonals in the top-right triangle are sorted in non-decreasing order.
#
# Example:
# Input: grid = [[1,7,3],[9,8,2],[4,5,6]]
#
# Output: [[8,2,3],[9,6,7],[4,5,1]]
#
# Explanation:
#
#
#
# The diagonals with a black arrow (bottom-left triangle) should be sorted in non-increasing order:
#
#
# 	[1, 8, 6] becomes [8, 6, 1].
# 	[9, 5] and [4] remain unchanged.
#
#
# The diagonals with a blue arrow (top-right triangle) should be sorted in non-decreasing order:
#
#
# 	[7, 2] becomes [2, 7].
# 	[3] remains unchanged.
#
# Constraints:
# grid.length == grid[i].length == n
# 	1 <= n <= 10
# 	-105 <= grid[i][j] <= 105
#

class Solution(object):
    def sortMatrix(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: List[List[int]]
        """
        n = len(grid)
        
        # Sort bottom-left diagonals in non-increasing order
        for col in range(n):
            diagonal = []
            r, c = 0, col
            while r < n and c >= 0:
                diagonal.append(grid[r][c])
                r += 1
                c -= 1
            diagonal.sort(reverse=True)
            r, c = 0, col
            for val in diagonal:
                grid[r][c] = val
                r += 1
                c -= 1
        
        for row in range(1, n):
            diagonal = []
            r, c = row, n - 1
            while r < n and c >= 0:
                diagonal.append(grid[r][c])
                r += 1
                c -= 1
            diagonal.sort(reverse=True)
            r, c = row, n - 1
            for val in diagonal:
                grid[r][c] = val
                r += 1
                c -= 1
        
        # Sort top-right diagonals in non-decreasing order
        for row in range(n):
            diagonal = []
            r, c = row, 0
            while r >= 0 and c < n:
                diagonal.append(grid[r][c])
                r -= 1
                c += 1
            diagonal.sort()
            r, c = row, 0
            for val in diagonal:
                grid[r][c] = val
                r -= 1
                c += 1
        
        for col in range(1, n):
            diagonal = []
            r, c = n - 1, col
            while r >= 0 and c < n:
                diagonal.append(grid[r][c])
                r -= 1
                c += 1
            diagonal.sort()
            r, c = n - 1, col
            for val in diagonal:
                grid[r][c] = val
                r -= 1
                c += 1
        
        return grid