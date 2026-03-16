# Source: https://leetcode.com/problems/matrix-similarity-after-cyclic-shifts/   |   Difficulty: Easy
#
# Problem Description:
# You are given an m x n integer matrix mat and an integer k. The matrix rows are 0-indexed.
#
# The following proccess happens k times:
#
#
# 	Even-indexed rows (0, 2, 4, ...) are cyclically shifted to the left.
#
#
#
#
#
# 	Odd-indexed rows (1, 3, 5, ...) are cyclically shifted to the right.
#
#
#
#
# Return true if the final modified matrix after k steps is identical to the original matrix, and false otherwise.
#
# Example:
# Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 4
#
# Output: false
#
# Explanation:
#
# In each step left shift is applied to rows 0 and 2 (even indices), and right shift to row 1 (odd index).
#
# Constraints:
# 1 <= mat.length <= 25
# 	1 <= mat[i].length <= 25
# 	1 <= mat[i][j] <= 25
# 	1 <= k <= 50
#

class Solution(object):
    def areSimilar(self, mat, k):
        """
        :type mat: List[List[int]]
        :type k: int
        :rtype: bool
        """
        m = len(mat)
        n = len(mat[0])
        
        # Calculate effective shifts
        left_shifts = k % n
        right_shifts = k % n
        
        for i in range(m):
            if i % 2 == 0:  # even-indexed row
                shifted_row = mat[i][left_shifts:] + mat[i][:left_shifts]
            else:  # odd-indexed row
                shifted_row = mat[i][-right_shifts:] + mat[i][:-right_shifts]
            
            if shifted_row != mat[i]:
                return False
        
        return True