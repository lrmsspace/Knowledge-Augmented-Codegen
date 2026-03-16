# Source: https://leetcode.com/problems/subarray-with-elements-greater-than-varying-threshold/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums and an integer threshold.
#
# Find any subarray of nums of length k such that every element in the subarray is greater than threshold / k.
#
# Return the size of any such subarray. If there is no such subarray, return -1.
#
# A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: nums = [1,3,4,3,1], threshold = 6
# Output: 3
# Explanation: The subarray [3,4,3] has a size of 3, and every element is greater than 6 / 3 = 2.
# Note that this is the only valid subarray.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i], threshold <= 109
#

class Solution(object):
    def validSubarraySize(self, nums, threshold):
        """
        :type nums: List[int]
        :type threshold: int
        :rtype: int
        """
        n = len(nums)
        left = [ -1 ] * n
        right = [ n ] * n
        stack = []
        
        for i in range(n):
            while stack and nums[stack[-1]] >= nums[i]:
                stack.pop()
            if stack:
                left[i] = stack[-1]
            stack.append(i)
        
        stack = []
        for i in range(n-1, -1, -1):
            while stack and nums[stack[-1]] >= nums[i]:
                stack.pop()
            if stack:
                right[i] = stack[-1]
            stack.append(i)
        
        for i in range(n):
            length = right[i] - left[i] - 1
            if nums[i] > threshold / length:
                return length
        
        return -1