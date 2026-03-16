# Source: https://leetcode.com/problems/contains-duplicate-ii/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array nums and an integer k, return true if there are two distinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.
#
# Example:
# Input: nums = [1,2,3,1], k = 3
# Output: true
#
# Constraints:
# 1 <= nums.length <= 105
# 	-109 <= nums[i] <= 109
# 	0 <= k <= 105
#

class Solution(object):
    def containsNearbyDuplicate(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: bool
        """
        num_dict = {}
        for i, num in enumerate(nums):
            if num in num_dict and i - num_dict[num] <= k:
                return True
            num_dict[num] = i
        return False