# Source: https://leetcode.com/problems/continuous-subarray-sum/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums and an integer k, return true if nums has a good subarray or false otherwise.
#
# A good subarray is a subarray where:
#
#
# 	its length is at least two, and
# 	the sum of the elements of the subarray is a multiple of k.
#
#
# Note that:
#
#
# 	A subarray is a contiguous part of the array.
# 	An integer x is a multiple of k if there exists an integer n such that x = n * k. 0 is always a multiple of k.
#
# Example:
# Input: nums = [23,2,4,6,7], k = 6
# Output: true
# Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 109
# 	0 <= sum(nums[i]) <= 231 - 1
# 	1 <= k <= 231 - 1
#

class Solution(object):
    def checkSubarraySum(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: bool
        """
        mod_map = {0: -1}  # Initialize with mod 0 at index -1
        current_sum = 0

        for i in range(len(nums)):
            current_sum += nums[i]
            mod = current_sum % k

            if mod in mod_map:
                if i - mod_map[mod] > 1:  # Ensure subarray length is at least 2
                    return True
            else:
                mod_map[mod] = i  # Store the first occurrence of this mod

        return False