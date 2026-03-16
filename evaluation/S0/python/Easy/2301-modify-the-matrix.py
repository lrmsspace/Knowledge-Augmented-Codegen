# Source: https://leetcode.com/problems/modify-the-matrix/   |   Difficulty: Easy
#
# Problem Description:
# Given a 0-indexed m x n integer matrix matrix, create a new 0-indexed matrix called answer. Make answer equal to matrix, then replace each element with the value -1 with the maximum element in its respective column.
#
# Return the matrix answer.
#
# Example:
# Input: matrix = [[1,2,-1],[4,-1,6],[7,8,9]]
# Output: [[1,2,9],[4,8,6],[7,8,9]]
# Explanation: The diagram above shows the elements that are changed (in blue).
# - We replace the value in the cell [1][1] with the maximum value in the column 1, that is 8.
# - We replace the value in the cell [0][2] with the maximum value in the column 2, that is 9.
#
# Constraints:
# m == matrix.length
# 	n == matrix[i].length
# 	2 <= m, n <= 50
# 	-1 <= matrix[i][j] <= 100
# 	The input is generated such that each column contains at least one non-negative integer.
#

class Solution(object):
    def modifiedMatrix(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[List[int]]
        """
        if not matrix or not matrix[0]:
            return matrix
        
        rows, cols = len(matrix), len(matrix[0])
        max_in_cols = [float('-inf')] * cols
        
        # Find the maximum in each column
        for j in range(cols):
            for i in range(rows):
                if matrix[i][j] != -1:
                    max_in_cols[j] = max(max_in_cols[j], matrix[i][j])
        
        # Replace -1 with the maximum in its column
        for i in range(rows):
            for j in range(cols):
                if matrix[i][j] == -1:
                    matrix[i][j] = max_in_cols[j]
        
        return matrix