# Source: https://leetcode.com/problems/spiral-matrix-iii/   |   Difficulty: Medium
#
# Problem Description:
# You start at the cell (rStart, cStart) of an rows x cols grid facing east. The northwest corner is at the first row and column in the grid, and the southeast corner is at the last row and column.
#
# You will walk in a clockwise spiral shape to visit every position in this grid. Whenever you move outside the grid's boundary, we continue our walk outside the grid (but may return to the grid boundary later.). Eventually, we reach all rows * cols spaces of the grid.
#
# Return an array of coordinates representing the positions of the grid in the order you visited them.
#
# Example:
# Input: rows = 1, cols = 4, rStart = 0, cStart = 0
# Output: [[0,0],[0,1],[0,2],[0,3]]
#
# Constraints:
# 1 <= rows, cols <= 100
# 	0 <= rStart < rows
# 	0 <= cStart < cols
#

class Solution(object):
    def spiralMatrixIII(self, rows, cols, rStart, cStart):
        """
        :type rows: int
        :type cols: int
        :type rStart: int
        :type cStart: int
        :rtype: List[List[int]]
        """
        result = []
        total_cells = rows * cols
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # right, down, left, up
        step_size = 1
        x, y = rStart, cStart
        result.append([x, y])
        
        while len(result) < total_cells:
            for direction in directions:
                for _ in range(step_size):
                    x += direction[0]
                    y += direction[1]
                    if 0 <= x < rows and 0 <= y < cols:
                        result.append([x, y])
                    if len(result) == total_cells:
                        return result
                if direction in [(0, -1), (0, 1)]:  # Increase step size after left and right moves
                    step_size += 1
        
        return result