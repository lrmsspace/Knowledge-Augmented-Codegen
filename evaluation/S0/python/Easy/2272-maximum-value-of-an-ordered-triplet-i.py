# Source: https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-i/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed integer array nums.
#
# Return the maximum value over all triplets of indices (i, j, k) such that i < j < k. If all such triplets have a negative value, return 0.
#
# The value of a triplet of indices (i, j, k) is equal to (nums[i] - nums[j]) * nums[k].
#
# Example:
# Input: nums = [12,6,1,2,7]
# Output: 77
# Explanation: The value of the triplet (0, 2, 4) is (nums[0] - nums[2]) * nums[4] = 77.
# It can be shown that there are no ordered triplets of indices with a value greater than 77.
#
# Constraints:
# 3 <= nums.length <= 100
# 	1 <= nums[i] <= 106
#

class Solution(object):
    def maximumTripletValue(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        max_value = 0
        
        for j in range(1, n - 1):
            max_left = max(nums[:j])
            max_right = max(nums[j + 1:])
            current_value = (max_left - nums[j]) * max_right
            max_value = max(max_value, current_value)
        
        return max_value