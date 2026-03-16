# Source: https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/   |   Difficulty: Medium
#
# Problem Description:
# Given an n x n matrix where each of the rows and columns is sorted in ascending order, return the kth smallest element in the matrix.
#
# Note that it is the kth smallest element in the sorted order, not the kth distinct element.
#
# You must find a solution with a memory complexity better than O(n2).
#
# Example:
# Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
# Output: 13
# Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15], and the 8th smallest number is 13
#
# Constraints:
# n == matrix.length == matrix[i].length
# 	1 <= n <= 300
# 	-109 <= matrix[i][j] <= 109
# 	All the rows and columns of matrix are guaranteed to be sorted in non-decreasing order.
# 	1 <= k <= n2
#
#
#  
# Follow up:
#
#
# 	Could you solve the problem with a constant memory (i.e., O(1) memory complexity)?
# 	Could you solve the problem in O(n) time complexity? The solution may be too advanced for an interview but you may find reading this paper fun.
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
    def kthSmallest(self, matrix, k):
        """
        :type matrix: List[List[int]]
        :type k: int
        :rtype: int
        """
        n = len(matrix)
        left, right = matrix[0][0], matrix[n - 1][n - 1]

        while left < right:
            mid = (left + right) // 2
            count = self.countLessEqual(matrix, mid)

            if count < k:
                left = mid + 1
            else:
                right = mid

        return left