# Source: https://leetcode.com/problems/magic-squares-in-grid/   |   Difficulty: Medium
#
# Problem Description:
# A 3 x 3 magic square is a 3 x 3 grid filled with distinct numbers from 1 to 9 such that each row, column, and both diagonals all have the same sum.
#
# Given a row x col grid of integers, how many 3 x 3 magic square subgrids are there?
#
# Note: while a magic square can only contain numbers from 1 to 9, grid may contain numbers up to 15.
#
# Example:
# Input: grid = [[4,3,8,4],[9,5,1,9],[2,7,6,2]]
# Output: 1
# Explanation: 
# The following subgrid is a 3 x 3 magic square:
#
# while this one is not:
#
# In total, there is only one magic square inside the given grid.
#
# Constraints:
# row == grid.length
# 	col == grid[i].length
# 	1 <= row, col <= 10
# 	0 <= grid[i][j] <= 15
#

class Solution(object):
    def numMagicSquaresInside(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        def isMagic(x, y):
            s = set()
            for i in range(3):
                for j in range(3):
                    s.add(grid[x + i][y + j])
            if len(s) != 9 or min(s) != 1 or max(s) != 9:
                return False
            target = sum(grid[x][y:y + 3])
            for i in range(3):
                if sum(grid[x + i][y:y + 3]) != target:
                    return False
            for j in range(3):
                if sum(grid[x + i][y + j] for i in range(3)) != target:
                    return False
            if sum(grid[x + i][y + i] for i in range(3)) != target:
                return False
            if sum(grid[x + i][y + 2 - i] for i in range(3)) != target:
                return False
            return True

        rows, cols = len(grid), len(grid[0])
        count = 0
        for i in range(rows - 2):
            for j in range(cols - 2):
                if isMagic(i, j):
                    count += 1
        return count