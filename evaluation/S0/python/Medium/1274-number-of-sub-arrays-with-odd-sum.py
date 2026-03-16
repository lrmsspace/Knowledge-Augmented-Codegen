# Source: https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers arr, return the number of subarrays with an odd sum.
#
# Since the answer can be very large, return it modulo 109 + 7.
#
# Example:
# Input: arr = [1,3,5]
# Output: 4
# Explanation: All subarrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
# All sub-arrays sum are [1,4,9,3,8,5].
# Odd sums are [1,9,3,5] so the answer is 4.
#
# Constraints:
# 1 <= arr.length <= 105
# 	1 <= arr[i] <= 100
#

class Solution(object):
    def numOfSubarrays(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        odd_count = 0
        even_count = 1  # empty subarray sum is even
        current_sum = 0
        result = 0

        for num in arr:
            current_sum += num
            if current_sum % 2 == 0:
                result = (result + odd_count) % MOD
                even_count += 1
            else:
                result = (result + even_count) % MOD
                odd_count += 1

        return result