# Source: https://leetcode.com/problems/transpose-matrix/   |   Difficulty: Easy
#
# Problem Description:
# Given a 2D integer array matrix, return the transpose of matrix.
#
# The transpose of a matrix is the matrix flipped over its main diagonal, switching the matrix's row and column indices.
#
# Example:
# Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
# Output: [[1,4,7],[2,5,8],[3,6,9]]
#
# Constraints:
# m == matrix.length
# 	n == matrix[i].length
# 	1 <= m, n <= 1000
# 	1 <= m * n <= 105
# 	-109 <= matrix[i][j] <= 109
#

class Solution(object):
    def transpose(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[List[int]]
        """
        if not matrix or not matrix[0]:
            return []

        rows, cols = len(matrix), len(matrix[0])
        transposed = [[0] * rows for _ in range(cols)]

        for r in range(rows):
            for c in range(cols):
                transposed[c][r] = matrix[r][c]

        return transposed