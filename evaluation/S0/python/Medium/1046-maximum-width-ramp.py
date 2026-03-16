# Source: https://leetcode.com/problems/maximum-width-ramp/   |   Difficulty: Medium
#
# Problem Description:
# A ramp in an integer array nums is a pair (i, j) for which i < j and nums[i] <= nums[j]. The width of such a ramp is j - i.
#
# Given an integer array nums, return the maximum width of a ramp in nums. If there is no ramp in nums, return 0.
#
# Example:
# Input: nums = [6,0,8,2,1,5]
# Output: 4
# Explanation: The maximum width ramp is achieved at (i, j) = (1, 5): nums[1] = 0 and nums[5] = 5.
#
# Constraints:
# 2 <= nums.length <= 5 * 104
# 	0 <= nums[i] <= 5 * 104
#

class Solution(object):
    def maxWidthRamp(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        left_min = [0] * n
        left_min[0] = nums[0]
        
        for i in range(1, n):
            left_min[i] = min(left_min[i - 1], nums[i])
        
        max_width = 0
        j = n - 1
        
        for i in range(n - 1, -1, -1):
            while j >= 0 and nums[j] >= left_min[i]:
                max_width = max(max_width, j - i)
                j -= 1
        
        return max_width