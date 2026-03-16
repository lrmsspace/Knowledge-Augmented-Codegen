# Source: https://leetcode.com/problems/reshape-the-matrix/   |   Difficulty: Easy
#
# Problem Description:
# In MATLAB, there is a handy function called reshape which can reshape an m x n matrix into a new one with a different size r x c keeping its original data.
#
# You are given an m x n matrix mat and two integers r and c representing the number of rows and the number of columns of the wanted reshaped matrix.
#
# The reshaped matrix should be filled with all the elements of the original matrix in the same row-traversing order as they were.
#
# If the reshape operation with given parameters is possible and legal, output the new reshaped matrix; Otherwise, output the original matrix.
#
# Example:
# Input: mat = [[1,2],[3,4]], r = 1, c = 4
# Output: [[1,2,3,4]]
#
# Constraints:
# m == mat.length
# 	n == mat[i].length
# 	1 <= m, n <= 100
# 	-1000 <= mat[i][j] <= 1000
# 	1 <= r, c <= 300
#

class Solution(object):
    def matrixReshape(self, mat, r, c):
        """
        :type mat: List[List[int]]
        :type r: int
        :type c: int
        :rtype: List[List[int]]
        """
        m = len(mat)
        n = len(mat[0]) if m > 0 else 0
        
        if m * n != r * c:
            return mat
        
        flat_list = [elem for row in mat for elem in row]
        reshaped_mat = []
        
        for i in range(r):
            new_row = flat_list[i * c:(i + 1) * c]
            reshaped_mat.append(new_row)
        
        return reshaped_mat