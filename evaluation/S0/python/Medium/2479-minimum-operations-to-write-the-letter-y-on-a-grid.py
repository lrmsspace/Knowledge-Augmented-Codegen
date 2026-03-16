# Source: https://leetcode.com/problems/minimum-operations-to-write-the-letter-y-on-a-grid/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed n x n grid where n is odd, and grid[r][c] is 0, 1, or 2.
#
# We say that a cell belongs to the Letter Y if it belongs to one of the following:
#
#
# 	The diagonal starting at the top-left cell and ending at the center cell of the grid.
# 	The diagonal starting at the top-right cell and ending at the center cell of the grid.
# 	The vertical line starting at the center cell and ending at the bottom border of the grid.
#
#
# The Letter Y is written on the grid if and only if:
#
#
# 	All values at cells belonging to the Y are equal.
# 	All values at cells not belonging to the Y are equal.
# 	The values at cells belonging to the Y are different from the values at cells not belonging to the Y.
#
#
# Return the minimum number of operations needed to write the letter Y on the grid given that in one operation you can change the value at any cell to 0, 1, or 2.
#
# Example:
# Input: grid = [[1,2,2],[1,1,0],[0,1,0]]
# Output: 3
# Explanation: We can write Y on the grid by applying the changes highlighted in blue in the image above. After the operations, all cells that belong to Y, denoted in bold, have the same value of 1 while those that do not belong to Y are equal to 0.
# It can be shown that 3 is the minimum number of operations needed to write Y on the grid.
#
# Constraints:
# 3 <= n <= 49 
# 	n == grid.length == grid[i].length
# 	0 <= grid[i][j] <= 2
# 	n is odd.
#

class Solution(object):
    def minimumOperationsToWriteY(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        y_cells = set()
        
        # Collect Y cells
        for i in range(n):
            y_cells.add((i, i))  # Main diagonal
            y_cells.add((i, n - 1 - i))  # Anti diagonal
        for i in range(n // 2, n):
            y_cells.add((i, n // 2))  # Vertical line
        
        count_y = [0, 0, 0]
        count_non_y = [0, 0, 0]
        
        for r in range(n):
            for c in range(n):
                if (r, c) in y_cells:
                    count_y[grid[r][c]] += 1
                else:
                    count_non_y[grid[r][c]] += 1
        
        min_operations = float('inf')
        
        for y_val in range(3):
            for non_y_val in range(3):
                if y_val != non_y_val:
                    operations = (sum(count_y) - count_y[y_val]) + (sum(count_non_y) - count_non_y[non_y_val])
                    min_operations = min(min_operations, operations)
        
        return min_operations