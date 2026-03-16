# Source: https://leetcode.com/problems/largest-number-at-least-twice-of-others/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array nums where the largest integer is unique.
#
# Determine whether the largest element in the array is at least twice as much as every other number in the array. If it is, return the index of the largest element, or return -1 otherwise.
#
# Example:
# Input: nums = [3,6,1,0]
# Output: 1
# Explanation: 6 is the largest integer.
# For every other number in the array x, 6 is at least twice as big as x.
# The index of value 6 is 1, so we return 1.
#
# Constraints:
# 2 <= nums.length <= 50
# 	0 <= nums[i] <= 100
# 	The largest element in nums is unique.
#

class Solution(object):
    def dominantIndex(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        max_num = max(nums)
        max_index = nums.index(max_num)
        
        for i in range(len(nums)):
            if i != max_index and max_num < 2 * nums[i]:
                return -1
        
        return max_index