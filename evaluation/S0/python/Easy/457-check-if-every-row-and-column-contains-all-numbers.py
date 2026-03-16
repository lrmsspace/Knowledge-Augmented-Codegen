# Source: https://leetcode.com/problems/check-if-every-row-and-column-contains-all-numbers/   |   Difficulty: Easy
#
# Problem Description:
# An n x n matrix is valid if every row and every column contains all the integers from 1 to n (inclusive).
#
# Given an n x n integer matrix matrix, return true if the matrix is valid. Otherwise, return false.
#
# Example:
# Input: matrix = [[1,2,3],[3,1,2],[2,3,1]]
# Output: true
# Explanation: In this case, n = 3, and every row and column contains the numbers 1, 2, and 3.
# Hence, we return true.
#
# Constraints:
# n == matrix.length == matrix[i].length
# 	1 <= n <= 100
# 	1 <= matrix[i][j] <= n
#

class Solution(object):
    def checkValid(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: bool
        """
        n = len(matrix)
        
        # Check each row
        for row in matrix:
            if set(row) != set(range(1, n + 1)):
                return False
        
        # Check each column
        for col in range(n):
            if set(matrix[row][col] for row in range(n)) != set(range(1, n + 1)):
                return False
        
        return True