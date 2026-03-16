# Source: https://leetcode.com/problems/first-completely-painted-row-or-column/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array arr, and an m x n integer matrix mat. arr and mat both contain all the integers in the range [1, m * n].
#
# Go through each index i in arr starting from index 0 and paint the cell in mat containing the integer arr[i].
#
# Return the smallest index i at which either a row or a column will be completely painted in mat.
#
# Example:
# Input: arr = [1,3,4,2], mat = [[1,4],[2,3]]
# Output: 2
# Explanation: The moves are shown in order, and both the first row and second column of the matrix become fully painted at arr[2].
#
# Constraints:
# m == mat.length
# 	n = mat[i].length
# 	arr.length == m * n
# 	1 <= m, n <= 105
# 	1 <= m * n <= 105
# 	1 <= arr[i], mat[r][c] <= m * n
# 	All the integers of arr are unique.
# 	All the integers of mat are unique.
#

class Solution(object):
    def firstCompleteIndex(self, arr, mat):
        """
        :type arr: List[int]
        :type mat: List[List[int]]
        :rtype: int
        """
        m, n = len(mat), len(mat[0])
        row_count = [0] * m
        col_count = [0] * n
        position = {}
        
        for r in range(m):
            for c in range(n):
                position[mat[r][c]] = (r, c)
        
        for i in range(len(arr)):
            r, c = position[arr[i]]
            row_count[r] += 1
            col_count[c] += 1
            
            if row_count[r] == n or col_count[c] == m:
                return i
        
        return -1