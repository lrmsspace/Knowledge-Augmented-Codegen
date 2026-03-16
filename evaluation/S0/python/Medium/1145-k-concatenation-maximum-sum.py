# Source: https://leetcode.com/problems/k-concatenation-maximum-sum/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array arr and an integer k, modify the array by repeating it k times.
#
# For example, if arr = [1, 2] and k = 3 then the modified array will be [1, 2, 1, 2, 1, 2].
#
# Return the maximum sub-array sum in the modified array. Note that the length of the sub-array can be 0 and its sum in that case is 0.
#
# As the answer can be very large, return the answer modulo 109 + 7.
#
# Example:
# Input: arr = [1,2], k = 3
# Output: 9
#
# Constraints:
# 1 <= arr.length <= 105
# 	1 <= k <= 105
# 	-104 <= arr[i] <= 104
#

class Solution(object):
    def kConcatenationMaxSum(self, arr, k):
        """
        :type arr: List[int]
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        
        def kadane(array):
            max_ending_here = max_so_far = 0
            for x in array:
                max_ending_here = max(0, max_ending_here + x)
                max_so_far = max(max_so_far, max_ending_here)
            return max_so_far
        
        single_kadane = kadane(arr)
        if k == 1:
            return single_kadane % MOD
        
        double_kadane = kadane(arr * 2)
        total_sum = sum(arr)
        
        if total_sum > 0:
            result = double_kadane + (k - 2) * total_sum
        else:
            result = double_kadane
        
        return result % MOD