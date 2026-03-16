# Source: https://leetcode.com/problems/single-element-in-a-sorted-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once.
#
# Return the single element that appears only once.
#
# Your solution must run in O(log n) time and O(1) space.
#
# Example:
# Input: nums = [1,1,2,3,3,4,4,8,8]
# Output: 2
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 105
#

class Solution(object):
    def singleNonDuplicate(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        left, right = 0, len(nums) - 1
        
        while left < right:
            mid = left + (right - left) // 2
            
            # Ensure mid is even
            if mid % 2 == 1:
                mid -= 1
            
            if nums[mid] == nums[mid + 1]:
                left = mid + 2
            else:
                right = mid
        
        return nums[left]