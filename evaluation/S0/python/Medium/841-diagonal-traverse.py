# Source: https://leetcode.com/problems/diagonal-traverse/   |   Difficulty: Medium
#
# Problem Description:
# Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.
#
# Example:
# Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
# Output: [1,2,4,7,5,3,6,8,9]
#
# Constraints:
# m == mat.length
# 	n == mat[i].length
# 	1 <= m, n <= 104
# 	1 <= m * n <= 104
# 	-105 <= mat[i][j] <= 105
#

class Solution(object):
    def findDiagonalOrder(self, mat):
        """
        :type mat: List[List[int]]
        :rtype: List[int]
        """
        if not mat or not mat[0]:
            return []
        
        m, n = len(mat), len(mat[0])
        result = []
        for d in range(m + n - 1):
            if d % 2 == 0:
                r = min(d, m - 1)
                c = d - r
                while r >= 0 and c < n:
                    result.append(mat[r][c])
                    r -= 1
                    c += 1
            else:
                c = min(d, n - 1)
                r = d - c
                while c >= 0 and r < m:
                    result.append(mat[r][c])
                    r += 1
                    c -= 1
        return result