# Source: https://leetcode.com/problems/subarray-sums-divisible-by-k/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums and an integer k, return the number of non-empty subarrays that have a sum divisible by k.
#
# A subarray is a contiguous part of an array.
#
# Example:
# Input: nums = [4,5,0,-2,-3,1], k = 5
# Output: 7
# Explanation: There are 7 subarrays with a sum divisible by k = 5:
# [4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
#
# Constraints:
# 1 <= nums.length <= 3 * 104
# 	-104 <= nums[i] <= 104
# 	2 <= k <= 104
#

class Solution(object):
    def subarraysDivByK(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        count = 0
        prefix_sum = 0
        mod_count = {0: 1}  # Initialize with mod 0 occurring once

        for num in nums:
            prefix_sum += num
            mod = prefix_sum % k
            if mod < 0:  # Handle negative mods
                mod += k

            if mod in mod_count:
                count += mod_count[mod]
                mod_count[mod] += 1
            else:
                mod_count[mod] = 1

        return count