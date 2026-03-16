# Source: https://leetcode.com/problems/sum-of-floored-pairs/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer array nums, return the sum of floor(nums[i] / nums[j]) for all pairs of indices 0 <= i, j < nums.length in the array. Since the answer may be too large, return it modulo 109 + 7.
#
# The floor() function returns the integer part of the division.
#
# Example:
# Input: nums = [2,5,9]
# Output: 10
# Explanation:
# floor(2 / 5) = floor(2 / 9) = floor(5 / 9) = 0
# floor(2 / 2) = floor(5 / 5) = floor(9 / 9) = 1
# floor(5 / 2) = 2
# floor(9 / 2) = 4
# floor(9 / 5) = 1
# We calculate the floor of the division for every pair of indices in the array then sum them up.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 105
#

class Solution(object):
    def sumOfFlooredPairs(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        max_num = max(nums)
        freq = [0] * (max_num + 1)

        for num in nums:
            freq[num] += 1

        prefix_sum = [0] * (max_num + 1)
        for i in range(1, max_num + 1):
            prefix_sum[i] = prefix_sum[i - 1] + freq[i]

        result = 0
        for i in range(1, max_num + 1):
            if freq[i] == 0:
                continue
            for multiple in range(i, max_num + 1, i):
                left = multiple
                right = min(multiple + i - 1, max_num)
                count_in_range = prefix_sum[right] - prefix_sum[left - 1]
                result += freq[i] * count_in_range * (multiple // i)
                result %= MOD

        return result