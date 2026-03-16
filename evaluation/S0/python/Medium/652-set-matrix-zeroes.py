# Source: https://leetcode.com/problems/set-matrix-zeroes/   |   Difficulty: Medium
#
# Problem Description:
# Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.
#
# You must do it in place.
#
# Example:
# Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
# Output: [[1,0,1],[0,0,0],[1,0,1]]
#
# Constraints:
# m == matrix.length
# 	n == matrix[0].length
# 	1 <= m, n <= 200
# 	-231 <= matrix[i][j] <= 231 - 1
#
#
#  
# Follow up:
#
#
# 	A straightforward solution using O(mn) space is probably a bad idea.
# 	A simple improvement uses O(m + n) space, but still not the best solution.
# 	Could you devise a constant space solution?
#

class Solution(object):
    def setZeroes(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: None Do not return anything, modify matrix in-place instead.
        """
        rows = len(matrix)
        cols = len(matrix[0]) if rows > 0 else 0
        
        first_row_has_zero = any(matrix[0][j] == 0 for j in range(cols))
        first_col_has_zero = any(matrix[i][0] == 0 for i in range(rows))
        
        for i in range(1, rows):
            for j in range(1, cols):
                if matrix[i][j] == 0:
                    matrix[i][0] = 0
                    matrix[0][j] = 0
        
        for i in range(1, rows):
            for j in range(1, cols):
                if matrix[i][0] == 0 or matrix[0][j] == 0:
                    matrix[i][j] = 0
        
        if first_row_has_zero:
            for j in range(cols):
                matrix[0][j] = 0
        
        if first_col_has_zero:
            for i in range(rows):
                matrix[i][0] = 0