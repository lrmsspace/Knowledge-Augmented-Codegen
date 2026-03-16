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

class Solution(object):
    def maxAbsValExpr(self, arr1, arr2):
        """
        :type arr1: List[int]
        :type arr2: List[int]
        :rtype: int
        """
        res = 0
        n = len(arr1)
        for s1 in [1, -1]:
            for s2 in [1, -1]:
                max_val = -float('inf')
                for i in range(n):
                    val = s1 * arr1[i] + s2 * arr2[i] + i
                    res = max(res, val - max_val)
                    max_val = max(max_val, val)
        return res