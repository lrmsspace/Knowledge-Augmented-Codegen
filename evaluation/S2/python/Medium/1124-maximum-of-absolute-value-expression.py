# Source: https://leetcode.com/problems/maximum-of-absolute-value-expression/   |   Difficulty: Medium
#
# Problem Description:
# Given two arrays of integers with equal lengths, return the maximum value of:
#
# |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|
#
# where the maximum is taken over all 0 <= i, j < arr1.length.
#
# Example:
# Input: arr1 = [1,2,3,4], arr2 = [-1,4,5,6]
# Output: 13
#
# Constraints:
# 2 <= arr1.length == arr2.length <= 40000
# 	-10^6 <= arr1[i], arr2[i] <= 10^6
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
    def maxAbsValExpr(self, arr1, arr2):
        """
        :type arr1: List[int]
        :type arr2: List[int]
        :rtype: int
        """
        max_value = 0
        for i in range(4):
            max_value = max(max_value, self.helper(arr1, arr2, i))
        return max_value