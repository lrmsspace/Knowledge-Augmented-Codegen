# Source: https://leetcode.com/problems/special-positions-in-a-binary-matrix/   |   Difficulty: Easy
#
# Problem Description:
# Given an m x n binary matrix mat, return the number of special positions in mat.
#
# A position (i, j) is called special if mat[i][j] == 1 and all other elements in row i and column j are 0 (rows and columns are 0-indexed).
#
# Example:
# Input: mat = [[1,0,0],[0,0,1],[1,0,0]]
# Output: 1
# Explanation: (1, 2) is a special position because mat[1][2] == 1 and all other elements in row 1 and column 2 are 0.
#
# Constraints:
# m == mat.length
# 	n == mat[i].length
# 	1 <= m, n <= 100
# 	mat[i][j] is either 0 or 1.
#

class Solution(object):
    def numSpecial(self, mat):
        """
        :type mat: List[List[int]]
        :rtype: int
        """
        row_counts = [0] * len(mat)
        col_counts = [0] * len(mat[0])
        
        for i in range(len(mat)):
            for j in range(len(mat[0])):
                if mat[i][j] == 1:
                    row_counts[i] += 1
                    col_counts[j] += 1
        
        special_positions = 0
        for i in range(len(mat)):
            for j in range(len(mat[0])):
                if mat[i][j] == 1 and row_counts[i] == 1 and col_counts[j] == 1:
                    special_positions += 1
        
        return special_positions