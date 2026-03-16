# Source: https://leetcode.com/problems/degree-of-an-array/   |   Difficulty: Easy
#
# Problem Description:
# Given a non-empty array of non-negative integers nums, the degree of this array is defined as the maximum frequency of any one of its elements.
#
# Your task is to find the smallest possible length of a (contiguous) subarray of nums, that has the same degree as nums.
#
# Example:
# Input: nums = [1,2,2,3,1]
# Output: 2
# Explanation: 
# The input array has a degree of 2 because both elements 1 and 2 appear twice.
# Of the subarrays that have the same degree:
# [1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
# The shortest length is 2. So return 2.
#
# Constraints:
# nums.length will be between 1 and 50,000.
# 	nums[i] will be an integer between 0 and 49,999.
#

class Solution(object):
    def findShortestSubArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        count = {}
        left, right = {}, {}
        
        for i, num in enumerate(nums):
            if num not in left:
                left[num] = i
            right[num] = i
            count[num] = count.get(num, 0) + 1
        
        degree = max(count.values())
        min_length = len(nums)
        
        for num in count:
            if count[num] == degree:
                min_length = min(min_length, right[num] - left[num] + 1)
        
        return min_length