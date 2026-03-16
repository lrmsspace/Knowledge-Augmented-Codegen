# Source: https://leetcode.com/problems/row-with-maximum-ones/   |   Difficulty: Easy
#
# Problem Description:
# Given a m x n binary matrix mat, find the 0-indexed position of the row that contains the maximum count of ones, and the number of ones in that row.
#
# In case there are multiple rows that have the maximum count of ones, the row with the smallest row number should be selected.
#
# Return an array containing the index of the row, and the number of ones in it.
#
# Example:
# Input: mat = [[0,1],[1,0]]
# Output: [0,1]
# Explanation: Both rows have the same number of 1's. So we return the index of the smaller row, 0, and the maximum count of ones (1). So, the answer is [0,1].
#
# Constraints:
# m == mat.length 
# 	n == mat[i].length 
# 	1 <= m, n <= 100 
# 	mat[i][j] is either 0 or 1.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def rowAndMaximumOnes(self, mat):
        """
        :type mat: List[List[int]]
        :rtype: List[int]
        """
        max_ones = -1
        row_index = -1
        
        for i in range(len(mat)):
            count_ones = sum(mat[i])
            if count_ones > max_ones:
                max_ones = count_ones
                row_index = i
                
        return [row_index, max_ones]