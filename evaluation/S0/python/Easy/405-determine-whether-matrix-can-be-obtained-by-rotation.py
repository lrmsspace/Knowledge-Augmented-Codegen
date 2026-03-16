# Source: https://leetcode.com/problems/determine-whether-matrix-can-be-obtained-by-rotation/   |   Difficulty: Easy
#
# Problem Description:
# Given two n x n binary matrices mat and target, return true if it is possible to make mat equal to target by rotating mat in 90-degree increments, or false otherwise.
#
# Example:
# Input: mat = [[0,1],[1,0]], target = [[1,0],[0,1]]
# Output: true
# Explanation: We can rotate mat 90 degrees clockwise to make mat equal target.
#
# Constraints:
# n == mat.length == target.length
# 	n == mat[i].length == target[i].length
# 	1 <= n <= 10
# 	mat[i][j] and target[i][j] are either 0 or 1.
#

class Solution(object):
    def findRotation(self, mat, target):
        """
        :type mat: List[List[int]]
        :type target: List[List[int]]
        :rtype: bool
        """
        def rotate(matrix):
            n = len(matrix)
            rotated = [[0] * n for _ in range(n)]
            for i in range(n):
                for j in range(n):
                    rotated[j][n - 1 - i] = matrix[i][j]
            return rotated

        for _ in range(4):
            if mat == target:
                return True
            mat = rotate(mat)
        return False